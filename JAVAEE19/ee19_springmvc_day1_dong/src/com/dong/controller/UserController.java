package com.dong.controller;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.springframework.web.servlet.ModelAndView;
import org.springframework.web.servlet.mvc.Controller;

public class UserController implements Controller {

	@Override
	public ModelAndView handleRequest(HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		// 接受请求，接受参数，验证参数
		// 封装参数，调用业务方法
		// 返回视图
		ModelAndView mv = new ModelAndView();
		// 设置页面回显数据
		mv.addObject("first", "欢迎学习springmvc！");

		// 指定跳转的视图
		// 返回物理视图
//		mv.setViewName("/index.jsp");
		// 返回逻辑视图
		mv.setViewName("index");

		return mv;
	}
}
