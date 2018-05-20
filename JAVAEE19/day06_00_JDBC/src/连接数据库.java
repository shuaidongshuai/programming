import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import com.mysql.jdbc.Driver;

public class 连接数据库 {
	public static void main(String[] args) throws SQLException {
		//1.注册驱动（不建议使用）
		DriverManager.registerDriver(new com.mysql.jdbc.Driver());
		
		/*坏处1.创建Driver类的时候，会执行java.sql.DriverManager.registerDriver(new Driver());
		 * 		会导致注册两次（其实我在想，第一次我们不注册不就的了 ）直接new com.mysql.jdbc.Driver(); 我测试也是可以的
		 *   2.强烈依赖数据库驱动.jar
		*/
		
		//2.获取连接Connection
		Connection conn = DriverManager.getConnection("jdbc:mysql://127.0.0.1:3306/dong","root","dong");//前面是协议+子协议+ip+端口+数据库名
		
		//3.获得sql语句执行对象  Statement
		Statement statement = conn.createStatement();
		
		//4.执行sql语句，并返回结果
		ResultSet res = statement.executeQuery("SELECT * FROM day06 ORDER BY id DESC");
		
		//5.处理结果
		while(res.next()){
			//两种获取值得方法  一个是 数字，一个是列名，最好使用列名
			System.out.println("学号:"+res.getObject(1));
			System.out.println("姓名:"+res.getObject("name"));
			System.out.println("分数:"+res.getObject(3));
			System.out.println("注册时间:"+res.getObject("time"));
			System.out.println("--------------------------------------");
		}
		
		//6.关闭资源
		res.close();
		statement.close();
		conn.close();
	}

}
