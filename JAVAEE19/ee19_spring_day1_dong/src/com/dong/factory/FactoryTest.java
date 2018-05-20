package com.dong.factory;

import org.junit.Test;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

/*
 * 3种bean实例化方式：
 * 默认构造 
 * 静态工厂 
 * 实例工厂
 */
public class FactoryTest {
	@Test
	public void demo1(){
		String xmlPath = "com/dong/factory/beans.xml";
		ApplicationContext applicationContext = new ClassPathXmlApplicationContext(xmlPath);
		UserService userService = applicationContext.getBean("userService1", UserService.class);
		userService.addUser();
	}
	@Test
	public void demo2(){
		String xmlPath = "com/dong/factory/beans.xml";
		ApplicationContext applicationContext = new ClassPathXmlApplicationContext(xmlPath);
		UserService userService = applicationContext.getBean("userService2", UserService.class);
		userService.addUser();
	}
	@Test
	public void demo3(){
		String xmlPath = "com/dong/factory/beans.xml";
		ApplicationContext applicationContext = new ClassPathXmlApplicationContext(xmlPath);
		UserService userService = applicationContext.getBean("userService3", UserService.class);
		userService.addUser();
	}
}
