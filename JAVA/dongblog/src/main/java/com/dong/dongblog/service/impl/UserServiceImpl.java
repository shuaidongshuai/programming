package com.dong.dongblog.service.impl;

import com.dong.dongblog.dao.UserDao;
import com.dong.dongblog.dto.*;
import com.dong.dongblog.model.User;
import com.dong.dongblog.model.UserExample;
import com.dong.dongblog.security.AuthUserService;
import com.dong.dongblog.service.UserService;
import com.github.pagehelper.Page;
import com.github.pagehelper.PageHelper;
import com.github.pagehelper.PageInfo;
import org.apache.log4j.Logger;
import org.dozer.DozerBeanMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;

@Service
public class UserServiceImpl implements UserService {
    private static Logger logger = Logger.getLogger(UserServiceImpl.class);

    @Autowired
    private DozerBeanMapper dozerBeanMapper;

    @Autowired
    private UserDao userDao;

    @Autowired
    private AuthUserService authUserService;

    /**
     * 添加用户
     *
     * @param requestUserDto
     * @return
     */
    public ResponseUserDto add(RequestUserDto requestUserDto) {
        ResponseUserDto responseUser = new ResponseUserDto();
        responseUser.setSuccess(false);
        if (requestUserDto == null) {
            responseUser.setErrorMsg("RequestUserDto is null");
            return responseUser;
        }
        User user = dozerBeanMapper.map(requestUserDto, User.class);
        //username不能一样
        ResponseUserDto responseUserDto = findByUsername(requestUserDto.getUsername());
        if (!responseUserDto.isSuccess()) {
            responseUser.setErrorMsg("用户名已存在");
            return responseUser;
        }
        //默认角色USER
        user.setRole("ROLE_USER");
        //不加锁
        user.setIslock(false);
        //密码使用Bcrypt加密
        BCryptPasswordEncoder bCryptPasswordEncoder = new BCryptPasswordEncoder();
        String encodePassword = bCryptPasswordEncoder.encode(user.getPassword());
        user.setPassword(encodePassword);
        //设置默认头像
        user.setAvatar("/images/avatarDefault.png");

        userDao.insertSelective(user);

        responseUser.setSuccess(true);
        return responseUser;
    }

    /**
     * 删除用户（只有管理员有权限）
     * super_admin -> admin -> user
     *
     * @param id
     */
    public ResponseCommonDto delete(Long id) {
        userDao.deleteByPrimaryKey(id);
        ResponseCommonDto responseCommonDto = new ResponseCommonDto();
        responseCommonDto.setSuccess(true);
        return responseCommonDto;
    }

    /**
     * 更新用户
     *
     * @param requestUserDto
     */
    public ResponseCommonDto updateById(RequestUserDto requestUserDto) {
        //检查是否是当前用户
        authUserService.checkUser(requestUserDto.getId(), null);

        User user = dozerBeanMapper.map(requestUserDto, User.class);
        userDao.updateByPrimaryKeySelective(user);

        //更新缓存
        authUserService.updateUser(user);

        ResponseCommonDto responseCommonDto = new ResponseCommonDto();
        responseCommonDto.setSuccess(true);
        return responseCommonDto;
    }

    /**
     * 查询用户
     *
     * @param id
     * @return
     */
    public ResponseUserDto findById(Long id) {
        User user = userDao.selectByPrimaryKey(id);
        ResponseUserDto responseUser = user2ResponseUser(user);
        return responseUser;
    }

    @Override
    public ResponseUserDto findByNickname(String nickname) {
        UserExample userExample = new UserExample();
        UserExample.Criteria criteria = userExample.createCriteria();
        criteria.andNicknameEqualTo(nickname);
        List<User> users = userDao.selectByExample(userExample);
        if (users.size() == 0) {
            return new ResponseUserDto();
        }
        if (users.size() > 1) {
            logger.error("findByNickname user.size=" + users.size());
            return new ResponseUserDto();
        }
        ResponseUserDto responseUser = user2ResponseUser(users.get(0));
        return responseUser;
    }

    @Override
    public ResponseUserDto findByUsername(String username) {
        ResponseUserDto responseUser = new ResponseUserDto();
        responseUser.setSuccess(false);
        UserExample userExample = new UserExample();
        UserExample.Criteria criteria = userExample.createCriteria();
        criteria.andUsernameEqualTo(username);
        List<User> users = userDao.selectByExample(userExample);
        if (users.size() == 0) {
            return responseUser;
        }
        if (users.size() > 1) {
            logger.error("findByUsername user.size=" + users.size());
            responseUser.setErrorMsg("user number=" + users.size());
            return responseUser;
        }
        responseUser = user2ResponseUser(users.get(0));
        return responseUser;
    }

    /**
     * 查询用户列表
     *
     * @param pageNum
     * @param pageSize
     * @return
     */
    public ResponseUserListDto findList(int pageNum, int pageSize) {
        Page page = PageHelper.startPage(pageNum, pageSize);
        userDao.selectByExample(new UserExample());
        PageInfo pageInfo = new PageInfo(page.getResult());
        return assembleResponseUserListDto(pageInfo);
    }

    public ResponseUserListDto findListUsernameLike(int pageNum, int pageSize, String username) {
        Page<User> page = PageHelper.startPage(pageNum, pageSize);
        UserExample userExample = new UserExample();
        UserExample.Criteria criteria = userExample.createCriteria();
        criteria.andUsernameLike(username);
        userDao.selectByExample(userExample);
        PageInfo pageInfo = new PageInfo(page.getResult());
        return assembleResponseUserListDto(pageInfo);
    }

    @Override
    public ResponseUserDto user2ResponseUser(User user) {
        ResponseUserDto responseUserDto = new ResponseUserDto();
        responseUserDto.setSuccess(false);
        if(user == null){
            return responseUserDto;
        }
        UserDto userDto = user2dto(user);
        responseUserDto.setUser(userDto);
        responseUserDto.setSuccess(true);
        return responseUserDto;
    }

    @Override
    public ResponseUserListDto assembleResponseUserListDto(PageInfo pageInfo) {
        List<UserDto> userDtos = users2dto(pageInfo.getList());

        pageInfo.setList(userDtos);

        ResponseUserListDto responseUserListDto = new ResponseUserListDto();
        responseUserListDto.setPageInfo(pageInfo);
        responseUserListDto.setSuccess(true);
        return responseUserListDto;
    }

    @Override
    public ResponseCommonDto changeStatus(Long userId, String userStatus) {
        ResponseCommonDto responseCommonDto = new ResponseCommonDto();
        responseCommonDto.setSuccess(false);
        if(userId == null || userStatus == null){
            responseCommonDto.setErrorMsg("parameter is null");
            return responseCommonDto;
        }

        RequestUserDto requestUserDto = new RequestUserDto();
        requestUserDto.setId(userId);
        if(userStatus.equals("正常")){
            requestUserDto.setIslock(true);
        } else if(userStatus.equals("加锁")){
            requestUserDto.setIslock(false);
        }
        updateById(requestUserDto);
        responseCommonDto.setSuccess(true);
        return responseCommonDto;
    }

    @Override
    public ResponseCommonDto saveAvatar(Long userId, String avatarUrl) {
        User user = new User();
        user.setId(userId);
        user.setAvatar(avatarUrl);
        userDao.updateByPrimaryKeySelective(user);

        ResponseCommonDto responseCommonDto = new ResponseCommonDto();
        responseCommonDto.setSuccess(true);
        return responseCommonDto;
    }

    @Override
    public UserDto user2dto(User user) {
        UserDto userDto = dozerBeanMapper.map(user, UserDto.class);
        if (user.getIslock()) {
            userDto.setStatus("加锁");
        } else {
            userDto.setStatus("正常");
        }
        if("ROLE_USER".equals(user.getRole())){
            userDto.setRole("普通用户");
        } else if ("ROLE_ADMIN".equals(user.getRole())) {
            userDto.setRole("管理员");
        }
        return userDto;
    }

    @Override
    public List<UserDto> users2dto(List<User> users) {
        List<UserDto> userDtos = new ArrayList<>();
        for (User user : users) {
            UserDto userDto = user2dto(user);
            userDtos.add(userDto);
        }
        return userDtos;
    }


}
