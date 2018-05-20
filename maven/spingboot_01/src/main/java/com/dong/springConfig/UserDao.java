package com.dong.springConfig;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by ☆东★ on 2018/5/3.
 */
public class UserDao {
    public List<User> queryUserList() {
        List<User> result = new ArrayList<User>();
        // 模拟数据库的查询
        for (int i = 0; i < 6; i++) {
            User user = new User();
            user.setId(i);
            user.setUsername("username_" + i);
            user.setPassword("password_" + i);
            result.add(user);
        }
        return result;
    }
}
