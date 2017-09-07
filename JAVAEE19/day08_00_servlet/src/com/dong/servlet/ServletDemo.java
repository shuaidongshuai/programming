package com.dong.servlet;

import java.io.IOException;

import javax.servlet.Servlet;
import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;

//创建servlet第一种方法
public class ServletDemo implements Servlet {

	public void destroy() {
	}
	public ServletConfig getServletConfig() {
		return null;
	}
	public String getServletInfo() {
		return null;
	}
	public void init(ServletConfig arg0) throws ServletException {
	}
	public void service(ServletRequest arg0, ServletResponse arg1)
			throws ServletException, IOException {
		System.out.println("hello Servlet");
	}
	
}
