import static org.junit.Assert.*;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Properties;

import org.junit.Test;

//连接数据库的三种方式

public class 连接数据库2 {
	@Test
	public void test1() throws SQLException, ClassNotFoundException {
		//1.加载驱动
		Class.forName("com.mysql.jdbc.Driver");
		
		//2.获取连接Connection
		Properties info = new Properties();
		info.setProperty("user", "root");
		info.setProperty("password", "dong");
		Connection conn = DriverManager.getConnection("jdbc:mysql://127.0.0.1:3306/dong",info);
		
		
		//3.获得sql语句执行对象  Statement
		Statement statement = conn.createStatement();
		
		//4.执行sql语句，并返回结果
		ResultSet res = statement.executeQuery("SELECT * FROM day06 ORDER BY id DESC");
		
		//5.处理结果
		while(res.next()){
			System.out.println("学号:"+res.getObject(1));
			System.out.println("姓名:"+res.getObject(2));
			System.out.println("分数:"+res.getObject(3));
			System.out.println("注册时间:"+res.getObject(4));
			System.out.println("--------------------------------------");
		}
		
		//6.关闭资源
		res.close();
		statement.close();
		conn.close();
	}
	@Test
	public void test2() throws SQLException, ClassNotFoundException {
		//1.加载驱动
		Class.forName("com.mysql.jdbc.Driver");
		
		//2.获取连接Connection
		Properties info = new Properties();
		Connection conn = DriverManager.getConnection("jdbc:mysql://127.0.0.1:3306/dong?user=root&password=dong");
		
		
		//3.获得sql语句执行对象  Statement
		Statement statement = conn.createStatement();
		
		//4.执行sql语句，并返回结果
		ResultSet res = statement.executeQuery("SELECT * FROM day06 ORDER BY id DESC");
		
		//5.处理结果
		while(res.next()){
			System.out.println("学号:"+res.getObject(1));
			System.out.println("姓名:"+res.getObject(2));
			System.out.println("分数:"+res.getObject(3));
			System.out.println("注册时间:"+res.getObject(4));
			System.out.println("--------------------------------------");
		}
		
		//6.关闭资源
		res.close();
		statement.close();
		conn.close();
	}
}
