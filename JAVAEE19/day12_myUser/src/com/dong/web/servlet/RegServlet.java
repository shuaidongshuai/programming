package com.dong.web.servlet;

import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.util.Date;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.beanutils.BeanUtils;
import org.apache.commons.beanutils.ConvertUtils;
import org.apache.commons.beanutils.Converter;
import org.apache.commons.beanutils.locale.converters.DateLocaleConverter;

import com.dong.domain.User;
import com.dong.domain.UserForm;
import com.dong.service.UserService;
import com.dong.service.impl.UserServiceImpl;

public class RegServlet extends HttpServlet {

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		request.setCharacterEncoding("UTF-8");
		response.setContentType("text/html;charset=UTF-8");
		
		//获取表单数据前先，检验一下
		UserForm userForm = new UserForm();
		try {
			BeanUtils.populate(userForm, request.getParameterMap());
		} catch (Exception e1) {
			e1.printStackTrace();
		}
		
		if(!userForm.validate()){// 如果map中不为空，说明有错误信息
			request.setAttribute("uf", userForm);
			request.getRequestDispatcher("/reg.jsp").forward(request, response);
			return;
		}
		
		//获取表单数据
		User user = new User();
		try {
			//用来将一些 key-value 的值（例如 hashmap）映射到 bean 中的属性。
			//先定义form表单内容的Info对象(当然你要先写一个bean,这个bean中包含form表单中各个对象的属性)
			//——> populateBean(info, request.getParameterMap());（先将request内容转为Map类型）
			//——>BeanUtils.populate(info, propertyMap);（调用包中方法映射）
			
			//改变String类型为Date类型
			/*ConvertUtils.register(new Converter() {
				public Object convert(Class type, Object value) {
					Date date1 = null;
					if(value instanceof String){
						String date = (String)value;
						SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
						try {
							date1 = sdf.parse(date);
						} catch (ParseException e) {
							e.printStackTrace();
						}
					}
					return date1;
				}
			}, Date.class);*///上面这一大段话，可以用下面一行解决
			ConvertUtils.register(new DateLocaleConverter(), Date.class);//日期转化为字符串
			ConvertUtils.register(new DateLocaleConverter(), Date.class);//这里才能把日期加入到里面
			//不用ConvertUtils也行。。只是没有日期而已，，我们user.setBirthday(request.getParameter(birthday));这样单独设置也行
			BeanUtils.populate(user, request.getParameterMap());
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("BeanUtils.populate(user, request.getParameterMap())出错");
		}
		
		//调用业务逻辑
		UserService us = new UserServiceImpl();
		us.register(user);
		
		//分发转向
		response.getWriter().write("注册成功,1s后跳到主页");
		response.setHeader("refresh", "1,url="+request.getContextPath()+"/index.jsp");
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);
	}

}
