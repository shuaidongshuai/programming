package com.dong.controller;

import java.util.Date;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;

import com.dong.domain.User;
import com.dong.domain.UserCustom;

@Controller// 相当于 <bean class="UserController"/>
@RequestMapping("user")//多个类可能有同名的，所以多加一层
public class UserController {
	
	@RequestMapping(value="/hello.do", method={RequestMethod.GET,RequestMethod.POST})
	public String myHello() {
		return "index";// 跳转到index页面
	}
	
	@RequestMapping("receiveInt")
	public String receiveInt(Integer id) {
		System.out.println(id);
		return "index";// 跳转到index页面
	}
	
	//接受数组类型参数
	@RequestMapping("receiveInts")
	public String receiveInts(Integer[] ids) {
		System.out.println(ids);
		return "index";// 跳转到index页面
	}
	
	@RequestMapping("receiveStr")
	public String receiveStr(String name) {
		System.out.println(name);
		return "index";// 跳转到index页面
	}
	
	@RequestMapping("receiveUser")
	public String receiveUser(User user) {
		System.out.println(user);
		return "index";// 跳转到index页面
	}
	
	//接受包装类型参数
	@RequestMapping("receiveUserCustom")
	public String recieveUserCustom(UserCustom userCustom){
		System.out.println(userCustom);
		return "index";
	}
	
	//集合类型
	@RequestMapping("receiveList")
	public String recieveUserCustomList(UserCustom userCustom){
		System.out.println(userCustom.getUserList());
		return "index";
	}
	//集合类型
	@RequestMapping("receiveMap")
	public String recieveUserCustomMap(UserCustom userCustom){
		System.out.println(userCustom.getMaps());
		return "index";
	}
	
	//跳转到json页面
	@RequestMapping("toJson")
	public String toJson(){
		return "request";
	}
	//请求json返回json|@RequestBody(json->user) @ResponseBody(user->json)
	@RequestMapping("requestJson")
	public @ResponseBody User requestJson(@RequestBody User user){
		System.out.println(user);
		return user;
	}
	//请求pojo返回json
	@RequestMapping("requestPojo")
	public @ResponseBody User requestPojo(User user){
		System.out.println(user);
		return user;
	}
	
	//多视图支持
	@RequestMapping("multiView")
	public User multiView(){
		User user = new User();
		user.setUsername("大东");
		user.setSex("男");
		user.setAddress("重庆");
		user.setBirthday(new Date());
		return user;
	}
	
}
