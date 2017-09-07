package com.dong.servlet;

import java.io.IOException;
import java.util.Random;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class ServletDemo5 extends HttpServlet {

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		//统一编码
		response.setContentType("text/html;charset=UTF-8");
		/*//response.setHeader("refresh", "1");//1s刷新一次
		response.setIntHeader("refresh", 1);//和上面一样效果
		Random r = new Random();
		response.getWriter().write(r.nextInt(100)+"");*/
		
		//设置3秒跳到主页
		response.getWriter().write("注册成功，3秒后跳到主页");
		response.setHeader("refresh", "3;url=http://www.baidu.com");
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);
	}

}
