package JDBC;

import java.sql.Connection;
import java.sql.Date;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;
import java.text.SimpleDateFormat;

import org.junit.Test;

public class _1创建 {
	@Test
	public void test1() {
		try {
			//1.加载驱动
			Class.forName("com.mysql.jdbc.Driver");
			//2.获取连接Connection
			Connection conn = DriverManager.getConnection("jdbc:mysql://127.0.0.1:3306/school","root","dong");
			//3.获得sql语句执行对象  Statement
			Statement statement = conn.createStatement();
			//4.执行sql语句，并返回结果
			String sql = "insert into student values(2,222,'小马','woman','1996-2-2','沙哈拉沙漠')";
			int res = statement.executeUpdate(sql);
			if(res > 0){
				System.out.println("插入成功");
			}
			
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	@Test
	public void test3() {
		try {
			//1.加载驱动
			Class.forName("com.mysql.jdbc.Driver");
			//2.获取连接Connection
			Connection conn = DriverManager.getConnection("jdbc:mysql://127.0.0.1:3306/school","root","dong");
			//3.获得sql语句执行对象  Statement
			Statement statement = conn.createStatement();
			//4.执行sql语句，并返回结果
			String sql = "delete from student where id=2";
			int res = statement.executeUpdate(sql);
			if(res > 0){
				System.out.println("删除成功");
			}
			
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	@Test
	public void test2() {
		//1.加载驱动
		try {
			Class.forName("com.mysql.jdbc.Driver");
			//2.获取连接Connection
			Connection conn = DriverManager.getConnection("jdbc:mysql://127.0.0.1:3306/school","root","dong");
			//3.获得sql语句执行对象  Statement
			Statement statement = conn.createStatement();
			//4.执行sql语句，并返回结果
			String sql = "select * from student";
			ResultSet res = statement.executeQuery(sql);
			while(res.next()){
				System.out.println(res.getInt(1)+"\t"+res.getInt(2)+"\t"+res.getObject(3)+"\t"+res.getObject(4)+"\t"+res.getObject(5)+"\t"+res.getObject(6));
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	@Test
	public void test4() {
		try {
			Class.forName("com.mysql.jdbc.Driver");
			Connection conn = DriverManager.getConnection("jdbc:mysql://127.0.0.1:3306/school","root","dong");
			PreparedStatement pState = conn.prepareStatement("insert into student values(?,?,?,?,?,?)");
			pState.setInt(1, 3);
			pState.setInt(2, 333);
			pState.setString(3, "chen");
			pState.setString(4, "man");
			pState.setString(5, "1996-2-22");
			pState.setString(6, "America");
			pState.executeUpdate();
		} catch (Exception e) {
			e.printStackTrace();
		}
		
	}
}
