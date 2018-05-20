package com.dong.service;

import com.dong.domain.User;

/**
 * Created by ☆东★ on 2018/5/5.
 */
public interface UserService {
    public User findUserById(int id);

    public void addUser(User user);

    public User findUserByName(String name);
}
