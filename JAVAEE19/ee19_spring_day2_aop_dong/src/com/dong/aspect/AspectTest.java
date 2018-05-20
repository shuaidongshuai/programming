package com.dong.aspect;

import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class AspectTest {
	public static void main(String[] args) {
		String xmlPath = "com/dong/aspect/beans.xml";
		ApplicationContext applicationContext = new ClassPathXmlApplicationContext(xmlPath);
		UserService userService = (UserService) applicationContext.getBean("UserService");
		userService.addUser();
		userService.updateUser();
		userService.deleteUser();
	}
}
