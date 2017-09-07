package com.dong.login;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
//修改了好几次，比较完善了
public class DoLogin extends HttpServlet {

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		request.setCharacterEncoding("UTF-8");
		response.setContentType("text/html;charset=UTF-8");

		// 获取表单数据
		String username = request.getParameter("username");
		String pwd = request.getParameter("pwd");
		String remName = request.getParameter("remName");
		String remPwd = request.getParameter("remPwd");
		//下面这段是后来加上的，是为了这次保存了账号密码，可以拷贝地址，直接给浏览器进入用户，不会出现登录失败的情况
		if(username==null && pwd ==null){
			// 得到客户端保存的Cookie数据 一开始就判断是否有cookies
			Cookie[] cookies = request.getCookies();
			for (int i = 0; cookies != null && i < cookies.length; i++) {
				if ("name".equals(cookies[i].getName())) {// 判断是否保存过用户名
					username = cookies[i].getValue();
					remName = "checked='checked'";
					continue;
				}
				if (!"".equals(username) && "pwd".equals(cookies[i].getName())) {// 如果用户名不为空，那么验证是否之前保存过密码
					pwd = cookies[i].getValue();
					remPwd = "checked='checked'";
				}
			}
		}
		
		// 处理业务逻辑
		// 分发转向
		Cookie cName = new Cookie("name", username);
		Cookie cPwd = new Cookie("pwd", pwd);
		PrintWriter w = response.getWriter();
		if ("dong".equals(username) && "123".equals(pwd)) {// 登录成功
			if (remPwd == null) {
				cPwd.setMaxAge(0);
			} else {
				cPwd.setMaxAge(Integer.MAX_VALUE);
			}
			// 要先判断密码，因为如果用户名没有被保存，那么密码肯定会被删除，为了避免，不勾选保存用户名，勾选保存密码情况
			if (remName == null) {// 有可能这次登录的时候没有点 保存用户名
				cName.setMaxAge(0);// 删除 name cookie
				cPwd.setMaxAge(0);
			} else {
				cName.setMaxAge(Integer.MAX_VALUE);// MAX_VALUE = 2147483647
													// [0x7fffffff]
			}
			response.addCookie(cName);
			response.addCookie(cPwd);
			w.write("登录成功");
		} else {
			w.write("登录失败！");
			cPwd.setMaxAge(0);//登录失败清除密码
			response.addCookie(cPwd);
			// 设置2秒跳到重新登录
			response.setHeader("refresh", "2;url=" + request.getContextPath()
					+ "/servlet/Login");
		}
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);
	}

}
