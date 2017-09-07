package com.dong.servlet;


import java.io.IOException;

import javax.servlet.GenericServlet;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;

//创建servlet第2种方法
public class ServletDemo2 extends GenericServlet {

	@Override
	public void service(ServletRequest arg0, ServletResponse arg1)
			throws ServletException, IOException {
		// TODO Auto-generated method stub
		System.out.println("ServletDemo2**************");
	}

}
