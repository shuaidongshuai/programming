package com.dong.login;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import com.dong.entity.dbUser;
import com.dong.util.DbUtils;

public class Server {
	//服务端判断是否有这个人，并返回这个人的信息
	public dbUser findUser(String name,String pwd) {
		Connection conn = null;
		Statement state = null;
		ResultSet rs = null;
		dbUser u = null;
		
		try {
			conn = DbUtils.getConnection();
			state = conn.createStatement();
			rs = state.executeQuery("SELECT * FROM day06 WHERE NAME='"+name+"' AND PASSWORD='"+pwd+"'");
			if(rs.next()){//如果有数据那么第二行一定不为空
				u = new dbUser();
				u.setId(rs.getInt(1));
				u.setName(rs.getString(2));
				u.setScore(rs.getInt(3));
				u.setTime(rs.getDate(4));
			}
		} catch (SQLException e) {
			e.printStackTrace();
		} finally{
			DbUtils.closeAll(rs, state, conn);
		}
		return u;
	}
}
