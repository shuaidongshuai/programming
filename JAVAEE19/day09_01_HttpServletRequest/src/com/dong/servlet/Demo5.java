package com.dong.servlet;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/*	转发和重定向的区别
 * 
 * 	转发 request 由服务器执行
	客户端只发送一次请求
	地址栏不变★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
	转发能够传递数据***************************
	转发也是一个域对象
	servletContxt

	重定向 response 由客户端执行
	客户端发送两次请求
	地址栏会发生变化★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
	不能传递数据*******************************
	可以跳转到其它应用***************************
*/

public class Demo5 extends HttpServlet {

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		request.setCharacterEncoding("UTF-8");//告诉服务器用什么编码处理浏览器中的数据
		response.setContentType("text/html;charset=UTF-8");//响应数据的时候统一编码
		
		System.out.println("A:我想办事");
		System.out.println("B:我办不了，我可以帮你找人办事");
		
		//将非表单数据添加到request请求中
		request.setAttribute("code", "B:这个是我的好朋友，请你帮帮他");
		
		
		//将请求转到demo6中
		request.getRequestDispatcher("/servlet/Demo6").forward(request, response);
		//注：请求转发 不能跳转到其它应用  他的根目录始终是在/http://localhost:8080/下面
		//request.getRequestDispatcher("http://www.baidu.com").forward(request, response);//dispatcher 调度
		
		
		//重定向		(下面两个句子，不能同时执行)
		//request.getContextPath()代表了当前app名（day09_01_HttpServletRequest  目的：当我们换了文件名照样可以运行，不用改代码
		//response.sendRedirect(request.getContextPath()+"/servlet/Demo6");//redirect 更改（信件等）姓名地址; 改变方向
		//注：重定向可以跳转到其它应用
		//response.sendRedirect("http://www.baidu.com/");
		
		System.out.println("B:事办完了");
		
		System.out.println("★★★★★下面是请求包含，相当于把Demo6中的代码直接copy到这里来★★★★★");
		
		request.getRequestDispatcher("/servlet/Demo6").include(request, response);
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);
	}

}
