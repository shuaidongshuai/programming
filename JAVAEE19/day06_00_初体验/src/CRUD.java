import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import org.junit.Test;

import com.dong.entity.dbUser;


public class CRUD {
	
	@Test
	public void testInsert() throws Exception{
		Class.forName("com.mysql.jdbc.Driver");
		
		//assign 分配
		Connection conn = DriverManager.getConnection("jdbc:mysql://127.0.0.1:3306/dong","root","dong");
		
		Statement state = conn.createStatement();
		
		int res = state.executeUpdate("INSERT INTO day06(`name`,`score`) VALUES('赵丽颖',77)");
		if(res>0){
			System.out.println("成功修改了"+res+"行");
		}else{
			System.out.println("修改了"+res+"行");
		}
	}
	@Test
	public void testDelete() throws Exception{
		Class.forName("com.mysql.jdbc.Driver");
		
		//assign 分配
		Connection conn = DriverManager.getConnection("jdbc:mysql://127.0.0.1:3306/dong","root","dong");
		
		Statement state = conn.createStatement();
		
		int res = state.executeUpdate("DELETE FROM day06 WHERE name='赵丽颖'");
		if(res>0){
			System.out.println("成功修改了"+res+"行");
		}else{
			System.out.println("修改了"+res+"行");
		}
	}
	@Test
	public void testUpdate() throws Exception{
		Class.forName("com.mysql.jdbc.Driver");
		
		//assign 分配
		Connection conn = DriverManager.getConnection("jdbc:mysql://127.0.0.1:3306/dong","root","dong");
		
		Statement state = conn.createStatement();
		
		int res = state.executeUpdate("UPDATE day06 SET NAME='杨幂',score='11' WHERE id=1002");
		if(res>0){
			System.out.println("成功修改了"+res+"行");
		}else{
			System.out.println("修改了"+res+"行");
		}
	}
	@Test
	public void testSelect() throws Exception{
		Class.forName("com.mysql.jdbc.Driver");
		
		//assign 分配
		Connection conn = DriverManager.getConnection("jdbc:mysql://127.0.0.1:3306/dong","root","dong");
		
		Statement state = conn.createStatement();
		
		ResultSet res = state.executeQuery("select * from day06");
		List<dbUser> list = new ArrayList<dbUser>();
		while(res.next()){
			dbUser u = new dbUser();
			//下面两种方式都可以获取值
			/*u.setId(res.getInt("id"));
			u.setName(res.getString("name"));
			u.setScore(res.getInt("score"));
			u.setTime(res.getDate("time"));*/
			u.setId((Integer)res.getObject(1));
			u.setName((String)res.getObject(2));
			u.setScore((Integer)res.getObject(3));
			u.setTime((Date)res.getObject(4));//注意这里调用的是sql的方法，但是要导util包，因为dbUser中导的是util包
			list.add(u);
			//两种获取值得方法  一个是 数字，一个是列名，最好使用列名
			/*System.out.println("学号:"+res.getObject(1));
			System.out.println("姓名:"+res.getObject("name"));
			System.out.println("分数:"+res.getObject(3));
			System.out.println("注册时间:"+res.getObject("time"));
			System.out.println("--------------------------------------");*/
		}
		//关闭资源
		res.close();
		state.close();
		conn.close();
		for(dbUser u:list){
			System.out.println(u);
		}
		
	}
}
