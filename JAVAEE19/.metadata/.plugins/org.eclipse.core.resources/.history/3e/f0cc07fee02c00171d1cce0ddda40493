package com.dong.Game;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.Map;
import java.util.Set;

import javax.servlet.ServletException;
import javax.servlet.ServletInputStream;
import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.dong.dao.Dao;
import com.dong.user.User;

public class Server extends HttpServlet {

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		response.setContentType("text/html;charset=UTF-8");
		request.setCharacterEncoding("UTF-8");
		
		/*
		 * 为什么要转码？  因为：get方式提交的参数编码，只支持iso8859-1编码。
		 */
		/* 创建User对象，还有转码 */
//String name2 = new String(request.getQueryString().getBytes("ISO8859-1"),"UTF-8");这样转码有问题，原因不太清楚
		String name = request.getParameter("name");
		String score = request.getParameter("score");
		System.out.println(name+"  ------------------------------ "+score);
		/* 在windows中需要把 iso8859-1 转化为UTF-8  但是在linux中好像直接就是UTF-8不需要转化。如果转换还要乱码*/
//		name = new String(name.getBytes("iso8859-1"),"UTF-8");
		User user = new User(name,score);

		/* 加入数据库 */
		Dao dao = new Dao();
		dao.addUser(user);
		
		/* 从数据库中获取排名 */
		String result = dao.getRank();
		
		ServletOutputStream out = response.getOutputStream();
		out.write(result.getBytes("UTF-8"));
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		response.setContentType("text/html;charset=UTF-8");
		request.setCharacterEncoding("UTF-8");
		
		/*	ServletOutputStream out = response.getOutputStream();
		//PrintWriter writer = response.getWriter(); 
		  Map<String, String[]> params = request.getParameterMap(); 
		  String queryString = "null";
		  int k = 0;
		  int j = 0;
		  for (String key : params.keySet()) { 
		  String[] values = params.get(key); 
		   for (int i = 0; i < values.length; i++) { 
		    String value = values[i];
		    queryString += "|" + value;
		  }
		}
	  // 去掉最后一个空格 
	  queryString = queryString.substring(0, queryString.length() - 1);
	  out.write(queryString.getBytes("UTF-8"));*/

		Map<String, String[]> params = request.getParameterMap(); 
		String[] queryString = new String[2];
		int j = 0;
		for (String key : params.keySet()) {
			String[] values = params.get(key);
			for (int i = 0; i < values.length; i++) {
				String value = values[i];
				queryString[j] = value;
				j++;
			}
		}

		User user = new User(queryString[0],queryString[1]);
		
		/* 加入数据库 */
		Dao dao = new Dao();
		dao.addUser(user);
		
		/* 从数据库中获取排名 */
		String result = dao.getRank();
		
		ServletOutputStream out = response.getOutputStream();
		out.write(result.getBytes("UTF-8"));
	}

}
