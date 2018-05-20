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

import com.dong.po.OrdersExt;

public class OrdersExtTest {
	private SqlSessionFactory sqlSessionFactory;
	@Before
	public void start() throws IOException{
		//读取全局配置文件
		InputStream inputStream = Resources.getResourceAsStream("SqlMapConfig.xml");
		//创建SqlSessionFactory
		sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);
	}
	@Test
	public void OrdersUserTest(){
		//创建sqlSession
		SqlSession sqlSession = sqlSessionFactory.openSession();
		//创建Dao---mapper
		OrdersMapper ordersMapper = sqlSession.getMapper(OrdersMapper.class);
		//进行Dao操作
		List<OrdersExt> ordersExtList = ordersMapper.findOrdersUser();
		//关闭sqlSession
		sqlSession.close();
		
		for(OrdersExt ordersExt : ordersExtList){
			System.out.println(ordersExt);
		}
	}
	@Test
	public void OrdersUserOrderdetailTest(){
		//创建sqlSession
		SqlSession sqlSession = sqlSessionFactory.openSession();
		//创建Dao---mapper
		OrdersMapper ordersMapper = sqlSession.getMapper(OrdersMapper.class);
		//进行Dao操作
		List<OrdersExt> ordersExtList = ordersMapper.findOrdersUserOrderdetail();
		//关闭sqlSession
		sqlSession.close();
		
		for(OrdersExt ordersExt : ordersExtList){
			System.out.println(ordersExt);
		}
	}
	@Test
	public void Orders2UserTest(){
		//创建sqlSession
		SqlSession sqlSession = sqlSessionFactory.openSession();
		//创建Dao---mapper
		UserMapper userMapper = sqlSession.getMapper(UserMapper.class);
		//进行Dao操作
		List<OrdersExt> orderExtList = userMapper.findOrderAndUserLazyLoading();
		//关闭sqlSession
		sqlSession.close();
		
		/* 最开始都会先查询select * from orders
		 * 如果没有延迟加载，当调用ordersExt.getUser()的时候，就会调用findUserById，查询所有user_id
		 * 如果有延迟加载，当调用ordersExt.getUser()的时候，就会调用findUserById，查询当前user_id
		 * 
		 * 延迟加载可以不让用户一开始等太久，每次访问才继续查询，但是我debug发现一个问题
		 * 不延迟，select * from user查询出来三个结果，但是有两个结果的user_id是相同的，所以user_id一共就两个
		 * 然后查询user的时候只需要调用两次select * from user id = #{id}
		 * 
		 * 延迟加载，两个相同id也会查询两次。。。这应该算是弊端吧
		 */
		for(OrdersExt ordersExt : orderExtList){
			System.out.println(ordersExt.getUser());
		}
	}
}
