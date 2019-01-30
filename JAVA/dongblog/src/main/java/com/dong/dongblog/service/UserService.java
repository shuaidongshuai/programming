package com.dong.dongblog.service;

import com.dong.dongblog.dto.*;
import com.dong.dongblog.model.User;
import com.github.pagehelper.PageInfo;

import java.util.List;

public interface UserService {
    ResponseUserDto add(RequestUserDto RequestUserDto);

    ResponseCommonDto delete(Long id);

    ResponseCommonDto updateById(RequestUserDto RequestUserDto);

    ResponseUserDto findById(Long id);

    ResponseUserDto findByNickname(String nickname);

    ResponseUserDto findByUsername(String nickname);

    ResponseUserListDto findList(int pageNum, int pageSize);

    ResponseUserListDto findListUsernameLike(int pageNum, int pageSize, String username);

    ResponseUserDto user2ResponseUser(User user);

    ResponseUserListDto assembleResponseUserListDto(PageInfo pageInfo);

    ResponseCommonDto changeStatus(Long userId, String userStatus);

    ResponseCommonDto saveAvatar(Long userId, String avatarUrl);

    UserDto user2dto(User user);

    List<UserDto> users2dto(List<User> users);
}
