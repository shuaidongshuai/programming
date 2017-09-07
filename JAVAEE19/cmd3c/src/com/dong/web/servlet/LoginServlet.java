package com.dong.web.servlet;

import java.io.IOException;
import java.lang.reflect.InvocationTargetException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.apache.commons.beanutils.BeanUtils;

import com.dong.domain.User;
import com.dong.service.UserService;
import com.dong.service.impl.UserServiceImpl;


public class LoginServlet extends HttpServlet {

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		request.setCharacterEncoding("UTF-8");
		//获取表单数据
		User user = new User();
		try {
			//因为我们只需要验证账号密码，所以不需要Conver转化字符串为时间
			BeanUtils.populate(user, request.getParameterMap());//把数据放到 user中
		} catch (IllegalAccessException e) {
			e.printStackTrace();
		} catch (InvocationTargetException e) {
			e.printStackTrace();
		}
		UserServiceImpl us = new UserServiceImpl();
		
		if(us.login(user) != null){
			//分发转向
			request.getSession().setAttribute("u", user);//保存到session中
			request.getRequestDispatcher("/index.jsp").forward(request, response);
		} else{
			request.setAttribute("u", user);//我只想显示一次
			request.getRequestDispatcher("/login.jsp").forward(request, response);
		}
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);
	}

}
