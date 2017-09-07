package com.dong.servlet;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class ServletDemo7 extends HttpServlet {

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		System.out.println("借点钱");
		System.out.println("我没有钱，我可以告诉你谁有钱");
		/*//告诉客服端重定向新的资源
		response.setStatus(302);
//★★★告诉浏览器要去哪(注意如果是服务器自己进行跳转，那么/ 代表的就是当前应用day09后面的地址，如果是浏览器那么 / 代表的就是8080后面的地址)★★★★★
		response.setHeader("location", "/day09_00_HttpServletResponse/servlet/ServletDemo1");*/
		
		//上面两句话也可以合成一句话
		response.sendRedirect("https://www.baidu.com/");//redirect 更改（信件等）姓名地址; 改变方向
		
		System.out.println("我走了");
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);
	}

}
