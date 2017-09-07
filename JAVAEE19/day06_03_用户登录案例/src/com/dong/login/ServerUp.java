package com.dong.login;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import com.dong.entity.dbUser;
import com.dong.util.DbUtils;

public class ServerUp {
	//Server这个类有bug   一种叫“sql注入”的东西会破坏他  比如我们在输入密码的时候加上      ' or '1'='1   就会出现bug
	//	SELECT * FROM day06 WHERE NAME='jfdsaio' AND PASSWORD='aa' or '1'='1';被or语句破坏		
	public dbUser findUser(String name, String pwd) {
		Connection conn = null;
		PreparedStatement preState = null;//★★★★★★★★★★★★★★★★★★★★★★
		ResultSet rs = null;
		dbUser u = null;
		try {
			conn = DbUtils.getConnection();
			//使用sql语句的预编译功能
			String sql = "SELECT * FROM day06 WHERE NAME=? AND PASSWORD=?";
			preState = conn.prepareStatement(sql);//得到执行sql语句的对象Statement
			//给？赋值
			preState.setString(1, name);
			preState.setString(2, pwd);
			//preState.setInt(3, fiosadjf);  如果有int那么就用这个
			rs = preState.executeQuery();
			
			
			if (rs.next()) {// 如果有数据那么第二行一定不为空
				u = new dbUser();
				u.setId(rs.getInt(1));
				u.setName(rs.getString(2));
				u.setScore(rs.getInt(3));
				u.setTime(rs.getDate(4));
			}
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			DbUtils.closeAll(rs, preState, conn);
		}
		return u;
	}
}
