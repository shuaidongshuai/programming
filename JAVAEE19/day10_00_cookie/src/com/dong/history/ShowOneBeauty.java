package com.dong.history;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.LinkedList;

import javax.servlet.ServletException;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.dong.DbUtil.Utils;
import com.dong.entity.Beauty;

public class ShowOneBeauty extends HttpServlet {

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		response.setContentType("text/html;charset=UTF-8");
		PrintWriter w = response.getWriter();
		
		//获取ShowAllbeauty中get方式传过来的id
		String id = request.getParameter("id");
		//通过id找MM
		Beauty beauty = Utils.findBeauty(id);
		w.print(beauty);
		
		//把当前浏览过的书的id写回到客户端
		String history = organizeId(id,request);//返回一个字符串，里面存储了浏览过的MMid
		Cookie cookie = new Cookie("history", history);
		cookie.setPath("/");
		cookie.setMaxAge(Integer.MAX_VALUE);
		response.addCookie(cookie);
	}
	/**
	 * 客户端							showAllBooks				showBookDetail
	 * 有Cookie，但没有historyBookId		1						historyBookId=1
	 * historyBookId=1					2						historyBookId=2-1
	 * historyBookId=1-2				2						historyBookId=2-1
	 * historyBookId=1-2-3				2						historyBookId=2-1-3
	 * historyBookId=1-2-3				4						historyBookId=4-1-2
	 */
	private String organizeId(String id, HttpServletRequest request) {
		//得到客户端的Cookie
		Cookie[] cks = request.getCookies();
		//查找有没有name叫做history的cookie
		Cookie historyCk = null;
		for (int i = 0;cks!=null && i < cks.length; i++) {
			if("history".equals(cks[i].getName())){
				historyCk = cks[i];
			}
		}
		if(historyCk == null){
			return id;
		}
		
		//取出原来的字符串
		String value = historyCk.getValue();
		//分割原来的字符串
		String[] split = value.split("-");
		//全部放到集合中
//		LinkedList(Collection<? extends E> c) 
//      					  构造一个包含指定 collection 中的元素的列表，这些元素按其 collection 的迭代器返回的顺序排列。
		LinkedList<String> list = new LinkedList<String>(Arrays.asList(split));//static List<T> asList 返回一个受指定数组支持的固定大小的列表
		
		if(list.contains(id)){//如果包含当前id的值，则删除这个id
			list.remove(id);
		}else if(list.size()>3){
			list.removeLast();//把最后一个id删除 
		}
		list.addFirst(id);//最新书的id添加到最前面
		
		StringBuffer sb = new StringBuffer();
		for (int i = 0; i < list.size(); i++) {
			if(0!=i){
				sb.append("-");
			}
			sb.append(list.get(i));
		}
		
		System.out.println(sb);
		System.out.println("id = "+id);
		
		return sb.toString();
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);
	}

}
