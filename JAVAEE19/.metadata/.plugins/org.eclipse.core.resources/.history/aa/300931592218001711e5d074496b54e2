package com.dong.web.servlet;

import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.util.Date;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.beanutils.BeanUtils;
import org.apache.commons.beanutils.ConvertUtils;
import org.apache.commons.beanutils.Converter;
import org.apache.commons.beanutils.locale.converters.DateLocaleConverter;

import com.dong.domain.User;
import com.dong.domain.UserForm;
import com.dong.service.UserService;
import com.dong.service.impl.UserServiceImpl;

public class RegServlet extends HttpServlet {

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		request.setCharacterEncoding("UTF-8");
		response.setContentType("text/html;charset=UTF-8");
		
		//获取表单数据前先，检验一下
		UserForm userForm = new UserForm();
		try {
			BeanUtils.populate(userForm, request.getParameterMap());
		} catch (Exception e1) {
			e1.printStackTrace();
		}
		
		if(!userForm.validate()){// 如果map中不为空，说明有错误信息
			request.setAttribute("uf", userForm);
			request.getRequestDispatcher("/reg.jsp").forward(request, response);
			return;
		}
		//获取表单数据
		User user = new User(userForm.getUsername(),userForm.getPassword(),userForm.getEmail(),userForm.getBirthday());
		
		//调用业务逻辑
		UserService us = new UserServiceImpl();
		us.register(user);
		
		//分发转向
		response.getWriter().write("注册成功,1s后跳到主页");
		response.setHeader("refresh", "1,url="+request.getContextPath()+"/index.jsp");
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);
	}

}
