package com.dong.servlet;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class Demo1 extends HttpServlet {

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
//		getMethod(); 获得请求方式
//		***getRequestURL();返回客户端发出请求时的完整URL。
//		***getRequestURI(); 返回请求行中的资源名部分。
//		*****getContextPath(); 当前应用的虚拟目录 /day09_01_HttpServletRequest
//		getQueryString() ; 返回请求行中的参数部分。
		
		System.out.println(request.getMethod());		// 	GET
		System.out.println(request.getRequestURL());	//http://localhost:8080/day09_01_HttpServletRequest/servlet/Demo1
		System.out.println(request.getRequestURI());	// /day09_01_HttpServletRequest/servlet/Demo1
		System.out.println(request.getContextPath());	// /day09_01_HttpServletRequest
		System.out.println(request.getQueryString());	// 在浏览器中输入什么就返回什么 比如加上?name=dong 就返回name=dong
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);
	}

}
