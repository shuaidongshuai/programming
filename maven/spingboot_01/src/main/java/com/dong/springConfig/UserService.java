package com.dong.springConfig;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

/**
 * Created by ☆东★ on 2018/5/3.
 */
@Service
public class UserService {
    @Autowired
    private UserDao userDao;
    public List<User> queryUserList(){
        return userDao.queryUserList();
    }
}
