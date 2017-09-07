package JDBC;

import java.sql.CallableStatement;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.Statement;

/**
 * 我们常用的操作数据库语言SQL语 句在执行的时候需要要先编译，然后执行，
 * 而存储过程（Stored Procedure）是一 组为了完成特定功能的SQL语句集，经编译后存储在数据库中，
 * 用户通过指定存储过程的名字并给定参数（如果该存储过程带有参 数）来调用执行它。
 * 
 * 下述过程就是：存储过程
 * 首先要在mysql 中部署好，然后用java代码得到结果
 * mysql> delimiter &		//改变结束标记为 &
 * mysql> create procedure Dong(in setAge int,out ave double)			//in 是待输入的变量   out将是取出来的数
    -> reads sql data													//固定
    -> begin
    -> select Avg(score) into ave from user where age>setAge;		//因为这里需要一个;结束符 所以上面要改成 &结束符
    -> end &
Query OK, 0 rows affected (0.00 sec)
 * mysql> delimiter ;		//恢复成 ;
 * 
 * @author ☆东★
 *
 */
public class _2数据库存储过程 {
	public static void main(String[] args) {
		try {
			//1.加载驱动
			Class.forName("com.mysql.jdbc.Driver");
			//2.获取连接Connection
			Connection conn = DriverManager.getConnection("jdbc:mysql://127.0.0.1:3306/test","root","dong");
//			//注册输入参数
			CallableStatement callstatement = conn.prepareCall("{call Dong(?,?)}");//我们创建带有几个参数的存储过程就要几个参数
			callstatement.setInt(1, 24);//设置第一个参数
			callstatement.registerOutParameter(2, java.sql.Types.DOUBLE);
			callstatement.execute();
			String average = String.format("%.1f", callstatement.getDouble(2));//得到结果
			System.out.println("student average score:" + average);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}

