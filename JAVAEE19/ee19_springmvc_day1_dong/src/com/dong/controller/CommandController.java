package com.dong.controller;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.springframework.validation.BindException;
import org.springframework.web.servlet.ModelAndView;
import org.springframework.web.servlet.mvc.AbstractCommandController;

import com.dong.domain.User;

public class CommandController extends AbstractCommandController{
	//构造的时候就指定参数绑定到那个javaBean
	public CommandController(){
		this.setCommandClass(User.class);
	}
	@Override
	protected ModelAndView handle(HttpServletRequest request,
			HttpServletResponse response, Object command, BindException errors)
			throws Exception {
		User user = (User) command;
		ModelAndView mv = new ModelAndView();
		mv.addObject("user", user);
		mv.setViewName("command");
		return mv;
	}

}
