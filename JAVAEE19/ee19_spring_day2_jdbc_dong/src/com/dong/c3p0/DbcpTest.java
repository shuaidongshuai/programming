package com.dong.c3p0;

import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

import com.dong.domain.User;

public class DbcpTest {
	public static void main(String[] args) {
		User user = new User(1, "帅东", "dong");
		String xmlPath = "com/dong/dbcp/beans.xml";
		ApplicationContext applicationContext = new ClassPathXmlApplicationContext(xmlPath);
		UserDao userDao = (UserDao) applicationContext.getBean("userDao");
		int resNum = userDao.update(user);
		System.out.println("成功修改：" + resNum + "行");
	}
}
