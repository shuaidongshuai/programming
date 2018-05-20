package com.dong.controller;

import com.dong.dao.UserMapper;
import com.dong.domain.User;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiImplicitParams;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

/**
 * Created by ☆东★ on 2018/5/12.
 */
@RestController
@RequestMapping("user")
public class UserController {
    @Autowired
    UserMapper userMapper;

    @ApiOperation(value = "根据Id获取User信息", notes = "处理/users/{id}的GET请求")
    @RequestMapping(value = "/{id}", method = RequestMethod.GET)
    public @ResponseBody User getUserById(@PathVariable Integer id){
        User user = userMapper.selectByPrimaryKey(id);
        return user;
    }
    @ApiOperation(value = "插入user", notes = "处理/users/的POST请求")
    @ApiImplicitParam(name = "user", value = "用户详细实体user", required = true, dataType = "User")
    @RequestMapping(value = "/", method = RequestMethod.POST)
    public String postUser(@RequestBody User user){
        userMapper.insert(user);
        return "success";
    }
    @ApiOperation(value = "删除User", notes = "处理/users/{id}的DELETE请求")
    @ApiImplicitParam(name = "id", value = "用户ID", required = true, dataType = "Integer", paramType = "path")   //paramType默认是body
    @RequestMapping(value = "/{id}", method = RequestMethod.DELETE)
    public String deleteUser(@PathVariable Integer id){
        userMapper.delete(id);
        return "success";
    }
    // 处理"/users/{id}"的PUT请求，用来更新User信息
    @ApiOperation(value = "更新User", notes = "处理/users/{id}的PUT请求(id用来演示，没有使用)")
    @ApiImplicitParams({
            @ApiImplicitParam(name = "id", value = "用户ID", required = false, dataType = "Long", paramType = "path"),
            @ApiImplicitParam(name = "user", value = "用户详细实体user", required = true, dataType = "User")
    })
    @RequestMapping(value = "/{id}", method = RequestMethod.PUT)
    public String putUser(@PathVariable Integer id, @RequestBody User user){
        userMapper.updateByPrimaryKey(user);
        return "success";
    }

}
