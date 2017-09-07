package com.dong.Context;

import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

//向下传递事件
public class ContextDemo5 extends HttpServlet {

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		//浏览器
		System.out.println("帮我一下");
		
		//第一次响应
		System.out.println("我帮不了，我找人帮你吧");
		
		//请求，向下传递
		ServletContext app = getServletContext();
		RequestDispatcher requestDispatcher = app.getRequestDispatcher("/servlet/ContextDemo6");
		requestDispatcher.forward(request, response);
		
		System.out.println("事办好了");
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);
	}

}
