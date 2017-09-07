package com.dong.servlet;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

//Servlet --> GenericServlet --> HttpServlet  (继承HttpServlet)
// 曾祖父  			          爷爷    			  	  爸爸    			 孙子
//创建servlet第3种方法
public class ServletDemo3 extends HttpServlet {

	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp)
			throws ServletException, IOException {
		System.out.println("++++++++doGet+++++++++++");
	}

	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse resp)
			throws ServletException, IOException {
		System.out.println("*********doPost***********");
	}

}
