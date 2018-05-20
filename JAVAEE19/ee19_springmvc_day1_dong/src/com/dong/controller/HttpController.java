package com.dong.controller;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.springframework.web.HttpRequestHandler;

public class HttpController implements HttpRequestHandler {

	@Override
	public void handleRequest(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		//给页面返回值
		request.setAttribute("first", "implements HttpRequestHandler 帅东");
		//跳转到物理视图
		request.getRequestDispatcher("index.jsp").forward(request, response);
	}
	
}
