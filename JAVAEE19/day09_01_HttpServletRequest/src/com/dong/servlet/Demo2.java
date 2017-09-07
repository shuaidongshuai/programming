package com.dong.servlet;

import java.io.IOException;
import java.util.Enumeration;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class Demo2 extends HttpServlet {

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		// 获取浏览器信息(request);

		// 获取消息头(request);

		// 获得相关name的消息头
		Enumeration headers = request.getHeaders("accept-language");
		while (headers.hasMoreElements()) {
			String e = (String) headers.nextElement();
			System.out.println(e + ":" + request.getHeader(e));
		}
	}

	private void 获取消息头(HttpServletRequest request) {
		// 获取所有消息头
		Enumeration names = request.getHeaderNames();
		while (names.hasMoreElements()) {
			String name = (String) names.nextElement();
			System.out.println(name + "：★" + request.getHeader(name));// request.getHeader(name)是获取某个消息头的内容
		}
	}

	private void 获取浏览器信息(HttpServletRequest request) {
		/*
		 * 一、什么是User-Agent User-Agent是Http协议中的一部分，属于头域的组成部分，User Agent也简称UA。
		 * 浏览器UA 字串的标准格式为： 浏览器标识 (操作系统标识; 加密等级标识; 浏览器语言) 渲染引擎标识 版本信息
		 */
		String header = request.getHeader("User-Agent");
		System.out.println(header);

		if (header.toLowerCase().contains("msie")) {
			System.out.println("你是用的浏览器是IE");
		} else if (header.toLowerCase().contains("chrome")) {
			System.out.println("你是用的是谷歌浏览器");
		}
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);
	}

}
