package com.dong.Context;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class ContextDemo3 extends HttpServlet {

	//获取全局配置信息
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		String encoding = getServletContext().getInitParameter("encoding");
		System.out.println(encoding);
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);
	}

}
