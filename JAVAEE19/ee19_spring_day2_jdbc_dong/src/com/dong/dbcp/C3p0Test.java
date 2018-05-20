package com.dong.dbcp;

import java.util.List;

import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

import com.dong.domain.User;

public class C3p0Test {
	public static void main(String[] args) {
		String xmlPath = "com/dong/c3p0/beans.xml";
		ApplicationContext applicationContext = new ClassPathXmlApplicationContext(xmlPath);
		UserDao userDao = (UserDao) applicationContext.getBean("userDao");
		List<User> allUser = userDao.findAll();
		for(User user : allUser){
			System.out.println(user);
		}
	}
}
