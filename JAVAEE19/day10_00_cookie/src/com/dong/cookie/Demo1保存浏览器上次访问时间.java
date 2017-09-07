package com.dong.cookie;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.Date;

import javax.servlet.ServletException;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
/*
	  name：名称不能唯一确定一个Cookie。路径可能不同。
	value：不能存中文。
	path：默认值是写Cookie的那个程序的访问路径
	比如：http://localhost:8080/day10_00_cookie/servlet/ck1写的Cookie
	path就是：/day10_00_cookie/servlet 看当前创建cookie的资源（servlet）文件路径 
	客户端在访问服务器另外资源时，根据访问的路径来决定是否带着Cookie到服务器
	当前访问的路径如果是以cookie的path开头的路径，浏览器就带。否则不带。
	
	maxAge：cookie的缓存时间。默认是-1（默认存在浏览器的内存中）。单位是秒。
	负数：cookie的数据存在浏览器缓存中
	0：删除。路径要保持一致，否则可能删错人。
	正数：缓存（持久化到磁盘上）的时间	*/
public class Demo1保存浏览器上次访问时间 extends HttpServlet {

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		response.setContentType("text/html;charset=UTF-8");
		PrintWriter pw = response.getWriter();
		
		//获取cookie
		//获取浏览器上次访问时间
		Cookie[] cookies = request.getCookies();
		for (int i = 0;cookies!=null && i < cookies.length; i++) {
			if("LastTime".equals(cookies[i].getName())){//如果cookies中有LastTime就打印
				Long time = Long.parseLong(cookies[i].getValue());//把cookies中的String类型转化为Long类型
				pw.write("你上次登录的时间是："+new Date(time).toLocaleString());//yyyy-MM-dd
			}
		}
		
		pw.print("<a href='"+request.getContextPath()+"/servlet/Demo3Clear'>删除cookie</a>");
		
		//把cookie写入到客服端
		//创建
		Cookie cookie = new Cookie("LastTime", System.currentTimeMillis()+"");
		
		//设置cookie的有效时间,单位是秒   
		System.out.println(cookie.getMaxAge());//如果不设置默认是-1  代表浏览器被关闭的时候自动清除cookie  
		cookie.setMaxAge(60*5);//保存5分钟（关闭浏览器后的5min）			   如果是0 那么就是不缓存cookie
		
		//设置cookie的path	下面三种都行
		//cookie.setPath("/day10_00_cookie");
		//cookie.setPath(request.getContextPath());
		cookie.setPath("/");
		
		//返回到客服端
		response.addCookie(cookie);
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);
	}

}
