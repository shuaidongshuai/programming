package com.dong.servlet;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class ServletDemo2 extends HttpServlet {
/*	PrintWriter以字符为单位，支持汉字，
	OutputStreamWriter以字节为单位，不支持汉字，

	处理人要看得懂的东西就用PrintWriter，字符
	处理机器看的东西就用OutputStreamWriter，二进制*/	
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		response.setContentType("text/html;charset=UTF-8");

		ServletOutputStream sos = response.getOutputStream();
		//sos.write("你好123".getBytes());// getBytes默认编码为本地编码（即：gbk）
		sos.write("你好123".getBytes("UTF-8"));//使用UTF-8
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);
	}

}
