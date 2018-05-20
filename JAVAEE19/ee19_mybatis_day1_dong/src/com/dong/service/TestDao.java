package com.dong.service;

import java.io.IOException;
import java.io.InputStream;
import java.util.List;

import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import com.dong.mapper.UserMapper;
import com.dong.po.User;

public class TestDao {
	private SqlSessionFactory sqlSessionFactory;
	//会在junit运行前执行
	@Before
	public void start() throws IOException{
		//读取全局配置文件
		InputStream inputStream = Resources.getResourceAsStream("SqlMapConfig.xml");
		//创建SqlSessionFactory
		sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);
	}
	@After
	public void end(){
		System.out.println("Junit执行结束-dong");
	}
	@Test
	public void testMapper() throws Exception{
		//创建sqlSession
		SqlSession sqlSession = sqlSessionFactory.openSession(true);
		//创建Dao -- 由mybatis完成
		UserMapper userMapper = sqlSession.getMapper(UserMapper.class);
		//进行Dao操作
		User user = userMapper.findUserById(1000);
		System.out.println("findUserById:"+user);
		
		List<User> listUser = userMapper.findUsersByName("东");
		System.out.println("findUsersByName:"+listUser);
		
		User insertUser = new User("刘德华", 80, "huazai");
		userMapper.insertUser(insertUser);
		System.out.println("insertUser:"+insertUser);
		
		sqlSession.close();
	}
}
