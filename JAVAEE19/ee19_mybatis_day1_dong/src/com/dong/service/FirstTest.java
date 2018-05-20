package com.dong.service;

import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;
import org.junit.Test;

import com.dong.po.User;
import com.dong.po.Users;

public class FirstTest {
	@Test
	public void demo1() throws Exception{
		//读取配置文件
		String resource = "SqlMapConfig.xml";
		InputStream resourceAsStream = Resources.getResourceAsStream(resource);
		//创建SqlSessionFactory
		SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(resourceAsStream);
		//创建sqlSession
		SqlSession sqlSession = sqlSessionFactory.openSession();
		//调用SqlSession的增删改查方法
		//第一个参数：表示statement的唯一标示	2.参数
		User user = sqlSession.selectOne("com.dong.findUserById", 1000);
		
		System.out.println(user);
		//关闭资源
		sqlSession.close();
	}
	@Test
	public void demo2() throws Exception{
		String resource = "SqlMapConfig.xml";
		InputStream resourceAsStream = Resources.getResourceAsStream(resource);
		SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(resourceAsStream);
		SqlSession sqlSession = sqlSessionFactory.openSession();
		List<User> list = sqlSession.selectList("com.dong.findUsersByName", "东");
		System.out.println(list);
		
		//关闭资源
		sqlSession.close();
	}
	@Test
	public void demo3() throws Exception{
		String resource = "SqlMapConfig.xml";
		InputStream resourceAsStream = Resources.getResourceAsStream(resource);
		SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(resourceAsStream);
		SqlSession sqlSession = sqlSessionFactory.openSession(true);
		
		User user = new User("冬雨", 520, "dongyu");
		sqlSession.insert("com.dong.insertUser", user);
		/*提交事务
		 * sqlSessionFactory.openSession()	默认是不自动提交的 
		 * sqlSessionFactory.openSession(true)	自动提交，这样就不用下面的comimt了
		 */
		//sqlSession.commit();
		// 关闭资源
		sqlSession.close();

		System.out.println("插入：" + user);
	}
	@Test
	public void demo4() throws Exception{
		//读取配置文件
		String resource = "SqlMapConfig.xml";
		InputStream resourceAsStream = Resources.getResourceAsStream(resource);
		//创建SqlSessionFactory
		SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(resourceAsStream);
		//创建sqlSession
		SqlSession sqlSession = sqlSessionFactory.openSession();
		//调用SqlSession的增删改查方法
		//第一个参数：表示statement的唯一标示	2.参数
		User user = sqlSession.selectOne("com.dong.findUserByIdRstMap", 1000);
		
		System.out.println(user);
		//关闭资源
		sqlSession.close();
	}
	@Test
	public void demo5() throws Exception{
		//读取配置文件
		String resource = "SqlMapConfig.xml";
		InputStream resourceAsStream = Resources.getResourceAsStream(resource);
		//创建SqlSessionFactory
		SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(resourceAsStream);
		//创建sqlSession
		SqlSession sqlSession = sqlSessionFactory.openSession();
		
		//查询id(1000,1020,1021) 
		ArrayList<Integer> idList = new ArrayList<Integer>();
		idList.add(1000);//陈明东
		idList.add(1020);//周冬雨
		idList.add(1021);//周星驰
		Users users = new Users();
		users.setIdList(idList);
		List<User> userList = sqlSession.selectList("com.dong.findUsersById", users);
		System.out.println("查询id(1000,1020,1021)："+userList);
		
		//查询id(1000,1020,1021) 含有“冬”的人
		User user = new User();
		user.setName("冬");
		users.setUser(user);
		userList = sqlSession.selectList("com.dong.findUsersById", users);
		System.out.println("查询id(1000,1020,1021) 含有“冬”的人："+userList);
		
		//关闭资源
		sqlSession.close();
	}
}
