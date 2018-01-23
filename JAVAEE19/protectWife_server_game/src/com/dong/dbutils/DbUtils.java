package com.dong.dbutils;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ResourceBundle;

public class DbUtils {
	private static String driverClass;
	private static String url;
	private static String username;
	private static String password;
	
	static{
		//加载properties文件
		ResourceBundle bundle = ResourceBundle.getBundle("dbinfo");
		driverClass = bundle.getString("driverClass");
		url = bundle.getString("url");
		username = bundle.getString("username");
		password = bundle.getString("password");
		//在静态块中直接注册驱动
		try {
			Class.forName(driverClass);
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public static Connection getConnection() throws SQLException{
		return DriverManager.getConnection(url,username,password);
	}
	//关闭资源的方法
	public static void closeAll(ResultSet rs,Statement state,Connection conn){
		//关闭的时候，判断是否为空
		if (rs != null) {
			try {
				rs.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		if (state != null) {
			try {
				state.close();
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
		if (conn != null) {
			try {
				conn.close();
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
	}
}
