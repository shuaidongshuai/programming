package com.dong.servlet;

import java.beans.IntrospectionException;
import java.beans.PropertyDescriptor;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.Enumeration;
import java.util.Map;

import javax.persistence.PrePersist;
import javax.servlet.ServletException;
import javax.servlet.ServletInputStream;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.beanutils.BeanUtils;

import com.dong.entity.User;

public class Server extends HttpServlet {

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		//告诉服务器使用什么编码，自己在html中用了什么编码，在这里就用什么编码，一般html默认UTF-8
		request.setCharacterEncoding("UTF-8");//这句话只对post提交有用
					//如果是get提交那么要用 new String(name.getBytes("iso-8859-1"),"UTF-8");对每一句话进行转化
		
		//获取表单数据
		/*ServletInputStream is = request.getInputStream();
		int len = 0;
		byte[] b = new byte[1024];
		while((len = is.read(b))!=-1){
			System.out.println(new String(b,0,len));
		}*/
		
		test4(request);
	}
	//用别人的矿建进行封装，只需要一句话
	private void test4(HttpServletRequest request) {
		User u = new User();
		System.out.println("封装前："+u);
		
		try {
			//用框架来封装数据	导入commons-beanutils-1.8.3.jar commons-logging-1.1.1.jar两个jar包
			BeanUtils.populate(u, request.getParameterMap());//只要一句话
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		System.out.println("封装后："+u);
	}
	//封装数据
	private void test3(HttpServletRequest request) {
		try {
			User u = new User();
			System.out.println("封装数据前"+u);
			//获取表单数据
			Map<String,String[]> map = request.getParameterMap();//全部放到map集合中
			//接口 Map<K,V> 有这样的方法 Set<Map.Entry<K,V>> entrySet()
			//Map中还有一个嵌套类static interface Map.Entry<K,V>  
			for (Map.Entry<String, String[]> m : map.entrySet()) {
				String name = m.getKey();
				String[] value = m.getValue();
				
				//创建属性描述器（找的是指定类中的get set方法，如果这个类没有很规范的写get set方法，那么就找不到）
				PropertyDescriptor pd = new PropertyDescriptor(name,User.class);
				//得到setter属性
				Method setter = pd.getWriteMethod();//得到可写属性
				
				if(value.length == 1){//如果值唯一的话
					setter.invoke(u, value[0]);//把值放到 u 中去
				}else{
					setter.invoke(u, (Object)value);//如果不加（Object） map会吧value拆成几个值，强转以后当成一个值
				}
			}
			System.out.println("封装数据后"+u);
			
//			上面看着复杂但是通用，下面这样一个一个弄也可以
//			String[] str = map.get("username");
//			u.setUsername(str);		//这样做也可以
//			System.out.println("姓名"+str[0]);
			
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	private void test2(HttpServletRequest request) {
		//获取表name名字
		Enumeration names = request.getParameterNames();//返回来的是一个枚举
		while(names.hasMoreElements()){
			String name = (String) names.nextElement();//得到名字
			String[] value = request.getParameterValues(name);//根据名字，得到值
			for (int i = 0;name!=null && i < value.length; i++) {
				System.out.println(name+"\t"+value[i]);
			}
		}
	}
	//获取表单数据
	private void test1(HttpServletRequest request) {
		//根据表单中name属性的名，获取value属性的值方法
		String username = request.getParameter("username");
		String pwd = request.getParameter("pwd");
		String sex = request.getParameter("sex");
		String[] hobby = request.getParameterValues("hobby");//这个有点不同，获取的是一个字符串数组
		String city = request.getParameter("city");
		
		System.out.println(username);
		System.out.println(pwd);
		System.out.println(sex);
		System.out.println(city);
		//System.out.println(hobby);//当hobby这一栏，没有被打钩就是null
		if(hobby==null){
			System.out.println("没有爱好");
		}else{
			for (int i = 0; i < hobby.length; i++) {
				System.out.println(hobby[i]+"\t");
			}
		}
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);
	}

}
