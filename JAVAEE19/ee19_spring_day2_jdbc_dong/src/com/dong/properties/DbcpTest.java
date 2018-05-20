package com.dong.properties;

import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

import com.dong.domain.User;

public class DbcpTest {
	public static void main(String[] args) {
		String xmlPath = "com/dong/properties/beans.xml";
		ApplicationContext applicationContext = new ClassPathXmlApplicationContext(xmlPath);
		UserDao userDao = (UserDao) applicationContext.getBean("userDao");
		User user = userDao.getById(1);
		System.out.println(user);
	}
}
