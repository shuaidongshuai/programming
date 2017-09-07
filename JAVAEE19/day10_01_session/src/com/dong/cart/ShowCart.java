package com.dong.cart;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.Map;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.dong.entity.Beauty;

public class ShowCart extends HttpServlet {

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		response.setContentType("text/html;charset=UTF-8");
		PrintWriter out = response.getWriter();
//3.1★查看是否有东西（获取session的值，如果没有值，返回null）
		//获取session
		HttpSession session = request.getSession();
		Map<String,Beauty> mapCart = (Map) session.getAttribute("cart");
//3.2★没有东西给个提醒
		if(mapCart==null){
			out.print("你还什么都没买呢");
			response.setHeader("refresh", "2;url="+request.getContextPath()+"/servlet/ShowCart");
			return ;
		}
		out.print("购物车有以下商品：<br/>");
//3.3★有东西就打印出来
		for (Map.Entry<String, Beauty> b : mapCart.entrySet()) {
			out.print(b.getValue().getName()+"\t"+b.getValue().getNum()+"个<br>");
		}
		
			//也可以用List集合
/*		List<Book> books = (List<Book>)session.getAttribute("cart");
		if(books==null){
			out.print("你还什么都没买呢");
			response.setHeader("refresh", "2;url="+request.getContextPath()+"/servlet/showAllBooksServlet");
			return;
		}
		for (Book book : books) {
			out.write(book.getName()+"<br/>");
		}*/
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);
	}

}
