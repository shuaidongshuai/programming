package com.dong.dao;

import java.io.UnsupportedEncodingException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import javax.management.RuntimeErrorException;

import com.dong.dbutils.DbUtils;
import com.dong.user.User;

public class Dao {
	
	public void addUser(User user){
		Connection conn = null;
		PreparedStatement pState = null;
		
		try {
			conn = DbUtils.getConnection();
			pState = conn.prepareStatement("INSERT INTO protectWife_game VALUES(?,?,?)");
			pState.setString(1, user.getLevel());
			pState.setString(2, user.getName());
			pState.setString(3, user.getScore());
			pState.executeUpdate();
		} catch (SQLException e) {
			e.printStackTrace();
			throw new RuntimeException("addUser失败");
		} finally{
			DbUtils.closeAll(null, pState, conn);
		}
	}
	
	public String getRank(User user){
		Connection conn = null;
		Statement state = null;
		ResultSet rs = null;
		String result = "null";
		
		try {
			conn = DbUtils.getConnection();
			state = conn.createStatement();
			rs = state.executeQuery("select name,score from protectWife_game where level="+user.getLevel()+" ORDER BY score DESC LIMIT 16");
			
			while(rs.next()){
				result += "|" + rs.getString(1) + "|" + rs.getInt(2);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		} finally{
			DbUtils.closeAll(rs, state, conn);
		}
		return result;
	}
}
