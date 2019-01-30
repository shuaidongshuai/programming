package com.dong.dongblog.service;

import com.dong.dongblog.dto.*;

public interface BlogService {
    /**
     * 保存blog
     * @param blogDto
     * @return
     */
    ResponseBlogSaveDto saveBlog(BlogDto blogDto);

    /**
     * 删除blog
     * @return
     */
    ResponseCommonDto deleteBlog(Long blogId);

    /**
     * 获取blog页面信息
     * @param blogId
     * @return
     */
    ResponseBlogPageDto getUserBlogById(Long blogId);

    /**
     * 获取某个用户的blog列表
     * @param userId
     * @return
     */
    ResponseUserBlogListDto getUserBlogList(Long userId, Integer pageNum, Integer pageSize);

    /**
     * 编辑博客
     * @param blogId
     * @return
     */
    ResponseBlogEditDto editBlog(Long blogId);

    /**
     * 点赞
     * @param blogId
     * @return
     */
    ResponseCommonDto voteBlog(Long blogId);

    /**
     * 取消点赞
     * @param blogId
     * @return
     */
    ResponseCommonDto cancelVoteBlog(Long blogId);
}
