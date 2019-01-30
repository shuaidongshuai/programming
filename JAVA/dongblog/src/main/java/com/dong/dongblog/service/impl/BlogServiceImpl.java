package com.dong.dongblog.service.impl;

import com.dong.dongblog.dao.BlogDao;
import com.dong.dongblog.dto.*;
import com.dong.dongblog.model.*;
import com.dong.dongblog.security.AuthUserService;
import com.dong.dongblog.service.*;
import com.github.pagehelper.Page;
import com.github.pagehelper.PageHelper;
import com.github.pagehelper.PageInfo;
import org.apache.log4j.Logger;
import org.dozer.DozerBeanMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

@Service
public class BlogServiceImpl implements BlogService {
    private static Logger logger = Logger.getLogger(BlogServiceImpl.class);

    @Autowired
    DozerBeanMapper dozerBeanMapper;

    @Autowired
    private BlogDao blogDao;

    @Autowired
    private UserService userService;

    @Autowired
    private AuthUserService authUserService;

    @Autowired
    private ConcernService concernService;

    @Autowired
    private BlogExtraMsgCache blogExtraMsgCache;

    @Autowired
    private VoteService voteService;

    @Autowired
    private ElasticsearchService elasticsearchService;

    @Override
    public ResponseBlogSaveDto saveBlog(BlogDto blogDto) {
        User user = authUserService.getCurUser();
        blogDto.setUserId(user.getId());
        BlogWithBLOBs blogWithBLOBs = BlogDto2do(blogDto);

        //自动生成摘要
        String contentHtml = blogWithBLOBs.getContentHtml();
        //删除html标签
        String txtcontent = contentHtml.replaceAll("</?[^>]+>", ""); //剔出<html>的标签
        String summary = txtcontent.replaceAll("<a>\\s*|\t|\r|\n</a>", "");
        //目前只是截取前面250个字
        if(txtcontent.length() > 200){
            summary = summary.substring(0, 200);
        }

        Date date = new Date();
        if(blogWithBLOBs.getId() == null){
            //初始化
            blogWithBLOBs.setCreateTime(date);
            blogWithBLOBs.setModifyTime(date);
            blogWithBLOBs.setTraffic(0);
            blogWithBLOBs.setVoteNum(0);
            blogWithBLOBs.setCommentNum(0);
            blogWithBLOBs.setSummary(summary);
            blogDao.insertSelective(blogWithBLOBs);
            elasticsearchService.addBlog(BlogWithBLOBs2Elasticsearch(blogWithBLOBs));
        } else{
            blogWithBLOBs.setModifyTime(date);
            blogDao.updateByPrimaryKeySelective(blogWithBLOBs);
            blogWithBLOBs.setCreateTime(date);
            blogWithBLOBs.setModifyTime(date);
            blogWithBLOBs.setTraffic(0);
            blogWithBLOBs.setVoteNum(0);
            blogWithBLOBs.setCommentNum(0);
            blogWithBLOBs.setSummary(summary);
            elasticsearchService.updateBlog(BlogWithBLOBs2Elasticsearch(blogWithBLOBs));
        }

        ResponseBlogSaveDto responseBlogSaveDto = new ResponseBlogSaveDto();
        responseBlogSaveDto.setSuccess(true);
        responseBlogSaveDto.setBlogId(blogWithBLOBs.getId());
        return responseBlogSaveDto;
    }

    @Override
    public ResponseCommonDto deleteBlog(Long blogId) {
        ResponseCommonDto responseCommonDto = new ResponseCommonDto();
        responseCommonDto.setSuccess(false);

        User user = authUserService.getCurUser();
        Long userId = user.getId();
        //检查是不是自己的blog
        BlogExample blogExample = new BlogExample();
        BlogExample.Criteria criteria = blogExample.createCriteria();
        criteria.andIdEqualTo(blogId).andUserIdEqualTo(userId);
        List<Blog> blogs = blogDao.selectByExample(blogExample);
        if(blogs.size() == 0){
            responseCommonDto.setErrorMsg("用户没有该博客");
            return responseCommonDto;
        }

        blogDao.deleteByPrimaryKey(blogId);
        elasticsearchService.delBlog(blogId);

        responseCommonDto.setSuccess(true);
        return responseCommonDto;
    }

    @Override
    public ResponseBlogPageDto getUserBlogById(Long blogId) {
        ResponseBlogPageDto responseBlogPageDto = new ResponseBlogPageDto();

        //每次进入一个完整blog页面都要修改阅读数
        BlogWithBLOBs blogWithBLOBs = blogDao.selectByPrimaryKey(blogId);

        //不需要返回content
        blogWithBLOBs.setContent("");

        //blogUserId
        Long blogUserId = blogWithBLOBs.getUserId();

        //获取除blog以外的扩展信息
        List<Integer> extraMsg = getUserBlogExtraMsg(blogUserId);

        //获取用户的信息
        ResponseUserDto responseUserDto = userService.findById(blogUserId);

        //前端展示nickname不超过13个字符
        String nickname = responseUserDto.getUser().getNickname();
        if(nickname.length() > 13){
            nickname = nickname.substring(0, 13) + "...";
        }

        //检查是否是当前用户的blog
        Boolean selfBlog = false;

        //是否关注过博客的主人
        Boolean concern = false;

        //是否点赞过这篇文章
        Boolean vote = false;

        User curUser = authUserService.getCurUser();
        if(curUser != null){
            selfBlog = isSelf(curUser.getId(), blogUserId);
            if(!selfBlog){
                ResponseCommonDto responseCommonDto = concernService.haveConcern(curUser.getId(), blogUserId);
                if(responseCommonDto.isSuccess()){
                    concern = true;
                }
                //不是博主，文章阅读数+1
                blogWithBLOBs.setTraffic(blogWithBLOBs.getTraffic() + 1);
                blogDao.updateByPrimaryKey(blogWithBLOBs);
            }
            //是否点赞
            vote = voteService.checkVote(curUser.getId(), blogId);
        } else{
            //不是博主，文章阅读数+1
            blogWithBLOBs.setTraffic(blogWithBLOBs.getTraffic() + 1);
            blogDao.updateByPrimaryKey(blogWithBLOBs);
        }

        //do->dto
        BlogDto blogDto = BlogWithBLOBsDo2dto(blogWithBLOBs);

        responseBlogPageDto.setBlogDto(blogDto);
        responseBlogPageDto.setArticleNum(extraMsg.get(0));
        responseBlogPageDto.setFansNum(extraMsg.get(1));
        responseBlogPageDto.setVoteNum(extraMsg.get(2));
        responseBlogPageDto.setCommentNum(extraMsg.get(3));
        responseBlogPageDto.setNickname(nickname);
        responseBlogPageDto.setAvatar(responseUserDto.getUser().getAvatar());
        responseBlogPageDto.setSelfBlog(selfBlog);
        responseBlogPageDto.setConcern(concern);
        responseBlogPageDto.setVote(vote);
        responseBlogPageDto.setSuccess(true);
        return responseBlogPageDto;
    }

    @Override
    public ResponseUserBlogListDto getUserBlogList(Long userId, Integer pageNum, Integer pageSize) {
        ResponseUserBlogListDto responseUserBlogListDto = new ResponseUserBlogListDto();
        responseUserBlogListDto.setSuccess(false);

        if(pageNum == null || pageSize == null){
            pageNum = 1;
            pageSize = 5;
        }

        if(userId == null){
            User curUser = authUserService.getCurUser();
            if(curUser == null){
                responseUserBlogListDto.setErrorMsg("错误的URL");
                return responseUserBlogListDto;
            }
            userId = curUser.getId();
        }

        //user
        ResponseUserDto responseUserDto = userService.findById(userId);
        if(!responseUserDto.isSuccess()){
            responseUserBlogListDto.setErrorMsg("没用此用户");
            return responseUserBlogListDto;
        }
        UserDto user = responseUserDto.getUser();


        Boolean selfBlog = false;
        User curUser = authUserService.getCurUser();
        if(curUser != null && curUser.getId().equals(userId)){
            selfBlog = true;
        }

        PageInfo pageInfo = getBlogListByUserId(userId, pageNum, pageSize);
        List<BlogDto> blogDtos = BlogDos2dto(pageInfo.getList());
        pageInfo.setList(blogDtos);

        //获取除blog以外的扩展信息
        List<Integer> extraMsg = getUserBlogExtraMsg(userId);

        responseUserBlogListDto.setPageInfo(pageInfo);
        responseUserBlogListDto.setUserId(userId);
        responseUserBlogListDto.setArticleNum(extraMsg.get(0));
        responseUserBlogListDto.setFansNum(extraMsg.get(1));
        responseUserBlogListDto.setVoteNum(extraMsg.get(2));
        responseUserBlogListDto.setCommentNum(extraMsg.get(3));
        responseUserBlogListDto.setNickname(user.getNickname());
        responseUserBlogListDto.setAvatar(user.getAvatar());
        responseUserBlogListDto.setSelfBlog(selfBlog);
        responseUserBlogListDto.setSuccess(true);
        return responseUserBlogListDto;
    }

    @Override
    public ResponseBlogEditDto editBlog(Long blogId) {
        User curUser = authUserService.getCurUser();
        if(curUser == null){
            throw new RuntimeException("editBlog user not exist");
        }

        String title = "", content = "";
        if(blogId != null){
            BlogWithBLOBs blogWithBLOBs = blogDao.selectByPrimaryKey(blogId);
            //检查是否是博主
            if(!blogWithBLOBs.getUserId().equals(curUser.getId())){
                throw new RuntimeException("editBlog blogUserId != curUserId");
            }
            title = blogWithBLOBs.getTitle();
            content = blogWithBLOBs.getContent();
        }

        ResponseBlogEditDto responseBlogEditDto = new ResponseBlogEditDto();
        responseBlogEditDto.setBlogId(blogId);
        responseBlogEditDto.setTitle(title);
        responseBlogEditDto.setContent(content);
        responseBlogEditDto.setUserId(curUser.getId());
        responseBlogEditDto.setNickName(curUser.getNickname());
        responseBlogEditDto.setAvatar(curUser.getAvatar());
        responseBlogEditDto.setSuccess(true);
        return responseBlogEditDto;
    }

    @Override
    public ResponseCommonDto voteBlog(Long blogId) {
        ResponseCommonDto responseCommonDto = new ResponseCommonDto();
        responseCommonDto.setSuccess(false);
        User curUser = authUserService.getCurUser();
        if(curUser == null){
            logger.warn("voteBlog 用户没有登录");
            responseCommonDto.setErrorMsg("用户没有登录");
            return responseCommonDto;
        }

        //vote
        ResponseCommonDto vote = voteService.vote(curUser.getId(), blogId);
        if(vote.isSuccess()){
            //blog
            BlogWithBLOBs blogWithBLOBs = blogDao.selectByPrimaryKey(blogId);
            if(blogWithBLOBs == null){
                responseCommonDto.setErrorMsg("没有此博客");
                return responseCommonDto;
            }
            blogWithBLOBs.setVoteNum(blogWithBLOBs.getVoteNum() + 1);
            blogDao.updateByPrimaryKeySelective(blogWithBLOBs);
            elasticsearchService.updateBlog(BlogWithBLOBs2Elasticsearch(blogWithBLOBs));
        } else {
            responseCommonDto.setErrorMsg(vote.getErrorMsg());
            return responseCommonDto;
        }

        responseCommonDto.setSuccess(true);
        return responseCommonDto;
    }

    @Override
    public ResponseCommonDto cancelVoteBlog(Long blogId) {
        ResponseCommonDto responseCommonDto = new ResponseCommonDto();
        responseCommonDto.setSuccess(false);
        User curUser = authUserService.getCurUser();
        if(curUser == null){
            logger.warn("cancelVoteBlog 用户没有登录");
            responseCommonDto.setErrorMsg("用户没有登录");
            return responseCommonDto;
        }

        //vote
        ResponseCommonDto cancelVote = voteService.cancelVote(curUser.getId(), blogId);
        if(cancelVote.isSuccess()){
            //blog
            BlogWithBLOBs blogWithBLOBs = blogDao.selectByPrimaryKey(blogId);
            if(blogWithBLOBs == null){
                responseCommonDto.setErrorMsg("没有此博客");
                return responseCommonDto;
            }
            blogWithBLOBs.setVoteNum(blogWithBLOBs.getVoteNum() - 1);
            blogDao.updateByPrimaryKeySelective(blogWithBLOBs);
            elasticsearchService.updateBlog(BlogWithBLOBs2Elasticsearch(blogWithBLOBs));
        } else {
            responseCommonDto.setErrorMsg(cancelVote.getErrorMsg());
            return responseCommonDto;
        }

        responseCommonDto.setSuccess(true);
        return responseCommonDto;
    }

    private List<Integer> getUserBlogExtraMsg(Long userId){
        List<Integer> extraMsg = blogExtraMsgCache.getAll(userId);
        if(extraMsg == null){
            extraMsg = new ArrayList<>(4);
            List<Blog> blogs = getAllBlogByUserId(userId);
            Integer voteNum = 0, commentNum = 0;
            for(Blog blog : blogs){
                voteNum += blog.getVoteNum();
                commentNum += blog.getCommentNum();
            }
            extraMsg.add(blogs.size());
            extraMsg.add(getFansNum(userId));
            extraMsg.add(voteNum);
            extraMsg.add(commentNum);
            blogExtraMsgCache.addAll(userId, extraMsg);
        }
        return extraMsg;
    }

    /**
     * 获取用户所有blog
     * @param userId
     * @return
     */
    private List<Blog> getAllBlogByUserId(Long userId){
        BlogExample blogExample = new BlogExample();
        BlogExample.Criteria criteria = blogExample.createCriteria();
        criteria.andUserIdEqualTo(userId);
        List<Blog> blogs = blogDao.selectByExample(blogExample);
        return blogs;
    }

    /**
     * 获取用户blog列表
     * @param userId
     * @param pageNum
     * @param pageSize
     * @return
     */
    private PageInfo getBlogListByUserId(Long userId, int pageNum, int pageSize){
        Page page = PageHelper.startPage(pageNum, pageSize);
        getAllBlogByUserId(userId);
        PageInfo pageInfo = new PageInfo(page.getResult());
        return pageInfo;
    }

    private Integer getFansNum(Long userId){
        List<Concern> fans = concernService.findFans(userId);
        return fans.size();
    }

    private BlogWithBLOBs BlogDto2do(BlogDto blogDto){
        BlogWithBLOBs blogWithBLOBs = dozerBeanMapper.map(blogDto, BlogWithBLOBs.class);
        return blogWithBLOBs;
    }

    private BlogDto BlogWithBLOBsDo2dto(BlogWithBLOBs blogWithBLOBs){
        BlogDto blogDto = dozerBeanMapper.map(blogWithBLOBs, BlogDto.class);
        return blogDto;
    }

    private BlogDto BlogDo2dto(Blog blog){
        BlogDto blogDto = dozerBeanMapper.map(blog, BlogDto.class);
        return blogDto;
    }

    private List<BlogDto> BlogDos2dto(List<Blog> blogs){
        List<BlogDto> blogDtos = new ArrayList<>(blogs.size());
        for(Blog blog : blogs){
            blogDtos.add(dozerBeanMapper.map(blog, BlogDto.class));
        }
        return blogDtos;
    }

    public Boolean isSelf(Long curUserId, Long blogUserId){
        if(curUserId.equals(blogUserId)){
            return true;
        }
        return false;
    }

    public ElasticsearchBlogDto BlogWithBLOBs2Elasticsearch(BlogWithBLOBs blogWithBLOBs){
        return dozerBeanMapper.map(blogWithBLOBs, ElasticsearchBlogDto.class);
    }

}
