package com.dong.mapper;

import java.io.IOException;
import java.io.InputStream;
import java.util.List;

import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;
import org.junit.Before;
import org.junit.Test;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

import com.dong.po.User;

public class UserTest {
	private ApplicationContext applicationContext;
	@Before
	public void start() throws IOException{
		applicationContext = new ClassPathXmlApplicationContext("spring/applicationContext.xml");
	}
	@Test
	public void OrdersUserTest(){
		UserMapper userMapper = (UserMapper) applicationContext.getBean("userMapper");
		User user = userMapper.findUserById(10);
		System.out.println(user);
	}
}
