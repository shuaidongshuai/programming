package com.dong.servlet;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

public class Demo2 extends HttpServlet {

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		response.setContentType("text/html;charset=UTF-8");
		HttpSession session = request.getSession();
		String name = (String) session.getAttribute("name");
		PrintWriter out = response.getWriter();
		if(name==null){
			out.write("Ã»ÓÐname"+"<br>"+session.getId());
		}else{
			out.write(name+"<br>"+session.getId());
		}
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);
	}

}
