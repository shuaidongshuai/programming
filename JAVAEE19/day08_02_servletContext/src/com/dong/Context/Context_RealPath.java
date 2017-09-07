package com.dong.Context;

import java.io.FileInputStream;
import java.io.IOException;
import java.util.Properties;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;


public class Context_RealPath extends HttpServlet {

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		String realPath1 = getServletContext().getRealPath("/WEB-INF/c.properties");
		String realPath2 = getServletContext().getRealPath("/WEB-INF/classes/b.properties");
		String realPath3 = getServletContext().getRealPath("WEB-INF/classes/com/dong/Context/a.properties");
		Properties pro = new Properties();
		
		
		pro.load(new FileInputStream(realPath1));
		System.out.println(pro.getProperty("key"));

		pro.load(new FileInputStream(realPath2));
		System.out.println(pro.getProperty("key"));
		
		pro.load(new FileInputStream(realPath3));
		System.out.println(pro.getProperty("key"));
		
		
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);
	}

}
