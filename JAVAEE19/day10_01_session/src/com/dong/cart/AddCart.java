package com.dong.cart;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.dong.DbUtil.Utils;
import com.dong.entity.Beauty;

public class AddCart extends HttpServlet {

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		response.setContentType("text/html;charset=UTF-8");
		PrintWriter out = response.getWriter();
//2.1★的到Cart传过来的Id，然后得到MM
		String id = request.getParameter("id");
		Beauty beauty = Utils.findBeauty(id);
		//得到session对象
		HttpSession session = request.getSession();
//2.2★查看购物车是否有东西，没有东西就创建一个购物车
		//从session中取出lMap（购物车）
		Map mapCart = (Map) session.getAttribute("cart");//先尝试取出数据，如果没有就创建一个Map集合
		if(mapCart==null){
			mapCart = new HashMap<String,Beauty>();
		}
//2.3★看是否有重复的商品
		//get(Object key) 返回指定键所映射的值；如果此映射不包含该键的映射关系，则返回 null。
		Beauty b = (Beauty) mapCart.get(id); 
		if(b==null){
			mapCart.put(id, beauty);
		}else{
			b.setNum(b.getNum()+1);
		}
//2.4★一定要设置session属性，所有记录都是从这里得到	
		session.setAttribute("cart", mapCart);//把list放回到session域中
		out.print("成功加入购物车！");
		//设置session有效时间
		session.setMaxInactiveInterval(60*5);//5min后消失
		//删除session,用于退出登录的时候
		//session.invalidate();
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);
	}

}
