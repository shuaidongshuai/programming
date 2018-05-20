package com.dong.aop;

import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class TestAop {
	public static void main(String[] args) {
		String xmlPath = "com/dong/aop/beans.xml";
		ApplicationContext applicationContext = new ClassPathXmlApplicationContext(xmlPath);
		UserService userService = (UserService) applicationContext.getBean("UserService");
		userService.addUser();
		userService.deleteUser();
		userService.updateUser();
	}
}
