import static org.junit.Assert.*;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Properties;

public class 关闭资源 {
	public static void main(String[] args) {
		Connection conn = null;
		Statement statement = null;
		ResultSet res = null;
		try {
			// 1.加载驱动
			Class.forName("com.mysql.jdbc.Driver");
			// 2.获取连接Connection
			Properties info = new Properties();
			conn = DriverManager
					.getConnection("jdbc:mysql://127.0.0.1:3306/dong?user=root&password=dong");

			// 3.获得sql语句执行对象 Statement
			statement = conn.createStatement();

			// 4.执行sql语句，并返回结果
			res = statement
					.executeQuery("SELECT * FROM day06 ORDER BY id DESC");

			// 5.处理结果
			while (res.next()) {
				System.out.println("学号:" + res.getObject(1));
				System.out.println("姓名:" + res.getObject(2));
				System.out.println("分数:" + res.getObject(3));
				System.out.println("注册时间:" + res.getObject(4));
				System.out.println("--------------------------------------");
			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			// 6.关闭资源
			if (res != null) {
				try {
					res.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			if (statement != null) {
				try {
					statement.close();
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
}
