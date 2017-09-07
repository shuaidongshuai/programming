package com.dong.login;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class Login保存用户名和密码 extends HttpServlet {

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		request.setCharacterEncoding("UTF-8");
		response.setContentType("text/html;charset=UTF-8");
		
		String username = "";
		String password = "";
		String checkedN = "";
		String checkedP = "";
		//得到客户端保存的Cookie数据					一开始就判断是否有cookies
		Cookie[] cookies = request.getCookies();
		for (int i = 0; cookies!=null && i <  cookies.length; i++) {
			if("name".equals(cookies[i].getName())){//判断是否保存过用户名
				username = cookies[i].getValue();
				checkedN = "checked='checked'";
				continue;
			}
			if(!"".equals(username) && "pwd".equals(cookies[i].getName())){//如果用户名不为空，那么验证是否之前保存过密码
				password = cookies[i].getValue();
				checkedP = "checked='checked'";
			}
		}
		
		//用servlet创建一个表单
		PrintWriter w = response.getWriter();
		w.write("<form action='"+request.getContextPath()+"/servlet/DoLogin' method='post'>");//提交表单，跳转到DoLogin中
		w.write("<p>&nbsp;&nbsp;&nbsp;账号登录<br></p>");
		w.write("<input type='text' name=username value="+username+"><br>");
		w.write("<input type='password' name=pwd value="+password+"><br>");
		w.write("<input type='checkbox' name=remName "+checkedN+">记住用户名");//remember
		w.write("<input type='checkbox' name=remPwd "+checkedP+">记住密码<br>");
		w.write("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type='submit' valur='登录'>");
		w.write("<form/>");
		
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);
	}

}
