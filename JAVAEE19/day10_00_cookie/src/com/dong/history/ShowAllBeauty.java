package com.dong.history;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.Iterator;
import java.util.Map;

import javax.servlet.ServletException;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.dong.DbUtil.Utils;
import com.dong.entity.Beauty;

public class ShowAllBeauty extends HttpServlet {

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		response.setContentType("text/html;charset=UTF-8");
		PrintWriter w = response.getWriter();
		w.print("<p>本网站出售各种美女</p><br>");
//0★从数据库中获取数据，并打印
		Map<String, Beauty> all = Utils.findAllBeauty();
		for (Map.Entry<String, Beauty> b : all.entrySet()) {
			w.print("<a href='" + request.getContextPath()
					+ "/servlet/ShowOneBeauty?id=" + b.getKey()
					+ "' target='_blank'>" + b.getValue().getName() + "<br>单价:"
					+ b.getValue().getPrice() + "</a><br><br>");
		}
		
		w.print("<hr>你最近浏览过:<br><br>");
		//获取cookie
		Cookie[] cookies = request.getCookies();
//1★找到我们所需要的cookie
		for (int i = 0; cookies!=null && i < cookies.length; i++) {
			if("history".equals(cookies[i].getName())){
				String value = cookies[i].getValue();
				String[] split = value.split("-");//储存了那几个数据的标号，如   1-2-3
//2★遍历我们这个cookie中的几个id号。。。cookie中只能存放字符串
				for (int j = 0; j < split.length; j++) {//遍历这几个数
					Beauty beauty = Utils.findBeauty(split[j]);
					w.print(beauty.getName()+"<br>");
				}
			}
		}
		
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);
	}

}
