package com.dong.cart;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.Map;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.dong.DbUtil.Utils;
import com.dong.entity.Beauty;

public class Cart extends HttpServlet {

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		response.setContentType("text/html;charset=UTF-8");
		PrintWriter out = response.getWriter();
		out.print("本网站有如下美眉<br><br>");
//1★从数据库中先取出一些MM，显示出来
		Map<String, Beauty> beauties = Utils.findAllBeauty();//获取MM集合
		for (Map.Entry<String, Beauty> b : beauties.entrySet()) {
//2★点击链接就算是购买了，转到AddCart界面
			out.print("<a href='"+request.getContextPath()+"/servlet/AddCart?id="+b.getKey()+"'>"+b.getValue().getName()+"<br>单价："+b.getValue().getPrice()+"</a><br><br>");
		
			//还可以这么写，作用是：在禁用cookie的时候，可以在url中传递session的id，就不用cookie进行传递
//			String url = request.getContextPath()+"/servlet/addCart?id="+book.getKey();
//			out.print("<a href='"+response.encodeURL(url)+"' >"+book.getValue().getName()+"</a><br/>");
		}
//3★转到查看购物车
		out.print("<hr><a href='"+request.getContextPath()+"/servlet/ShowCart'>查看购物车</a>");
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);
	}

}
