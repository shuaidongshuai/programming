package com.dong.controller;

import com.dong.domain.User;
import com.dong.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

/**
 * Created by ☆东★ on 2018/5/5.
 */
@Controller
@RequestMapping(value = "user")
public class UserController {
    @Autowired
    private UserService userService;

    @RequestMapping(value = "/")
    public String home() {
        return "index";
    }

    @RequestMapping(value = "getUserById/{id}", produces = {"application/json;charset=UTF-8"})
    @ResponseBody()
    public User getUserById(@PathVariable("id") int id){
        User user = userService.findUserById(id);
        return user;
    }

    @RequestMapping(value = "getUserByName/{name}", produces = {"application/json;charset=UTF-8"})
    @ResponseBody()
    public User getUserByName(@PathVariable("name") String name){
        User user = userService.findUserByName(name);
        return user;
    }

    @RequestMapping(value = "addUser")
    public @ResponseBody User addUser(User user){
        userService.addUser(user);
        return user;
    }

    @RequestMapping(value = "testUser")
    public @ResponseBody User testUser(@RequestBody User user){ //RequestBody会把请求消息体里面有所的数据转成json格式，然后再转成user
        return user;
    }
}
