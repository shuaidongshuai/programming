package com.dong.servlet;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class Demo6 extends HttpServlet {

	//添加非表单数据
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		response.setContentType("text/html;charset=UTF-8");//响应数据的时候统一编码
		String code = (String) request.getAttribute("code");
		System.out.println(code);

		//可以吧这个Attribute移除
		request.removeAttribute("code");
		System.out.println("再次尝试打印code："+(String) request.getAttribute("code"));
		
		System.out.println("C:事办好了");
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);
	}

}
