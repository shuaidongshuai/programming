package com.dong.servlet;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

public class Demo1 extends HttpServlet {

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		//获取name	从get方式中获取
		String name = request.getParameter("name");
		if(name == null){
			return;
		}
		name = new String(name.getBytes("iso-8859-1"),"UTF-8");
		//得到一个HttpSession对象
		HttpSession session = request.getSession();
		session.setAttribute("name", name);
		response.getWriter().print(session.getId());
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);
	}

}
