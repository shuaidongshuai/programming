package com.dong.servlet;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class ServletDemo1 extends HttpServlet {

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		//服务器默认编码ISO-8859-1，不支持中文，tomcat规定的
		
		/*//告诉服务器使用什么编码
		response.setCharacterEncoding("UTF-8");//不要这句话，那么服务器码表里面根本就查不到中文，有这句话了就能查到是中文
		//告诉客服端使用什么编码
		response.setHeader("content-type", "text/html;charset=UTF-8");//客服端必须和服务器用一样的编码解码格式
*/		
		//上面两句话可以合成一句话
		response.setContentType("text/html;charset=GBK");//只要同意编码就行了，而且这个编码里面需要有中文（如果我们有中文）
		
		PrintWriter out = response.getWriter();//得到一个字符输出流
		out.write("陈明东love!!!!!!!");//向客服端相应文本内容
		
		System.out.println("Demo1");
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);
	}

}
