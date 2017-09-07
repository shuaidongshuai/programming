package com.dong.servletConfig;

import java.io.IOException;

import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class ServletConfig1 extends HttpServlet {

/*	private ServletConfig config;

	@Override
	public void init(ServletConfig config) throws ServletException {
		this.config = config;
	}*/

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		//第一种方法
		//String value = config.getInitParameter("encoding");
		
		//第二种方法
		//String value = this.getServletConfig().getInitParameter("encoding");
		
		//第三种方法
		String value = this.getInitParameter("encoding");
		
		
		System.out.println(value);
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);
	}

}
