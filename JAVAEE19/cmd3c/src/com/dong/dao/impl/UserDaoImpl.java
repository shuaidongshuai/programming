package com.dong.dao.impl;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.text.SimpleDateFormat;

import com.dong.dao.UserDao;
import com.dong.dbutils.DbUtils;
import com.dong.domain.User;

public class UserDaoImpl implements UserDao {

	public void addUser(User user) {
		Connection conn = null;
		PreparedStatement ps = null;

		try {
			conn = DbUtils.getConnection();
			ps = conn.prepareStatement("INSERT INTO day12(username,password,email,birthday) VALUES(?,?,?,?)");
			ps.setString(1, user.getUsername());
			ps.setString(2, user.getPassword());
			ps.setString(3, user.getEmail());
			ps.setString(4, user.getBirthday());
			ps.executeUpdate();
		} catch (SQLException e) {
			e.printStackTrace();
			throw new RuntimeException("创建用户失败");
		} finally {
			DbUtils.closeAll(null, ps, conn);
		}
	}

	public User findUser(User user) {
		Connection conn = null;
		PreparedStatement ps = null;
		ResultSet rs = null;
		try {
			conn = DbUtils.getConnection();
			ps = conn.prepareStatement("SELECT * FROM day12 WHERE username=? AND PASSWORD=?");
			ps.setString(1, user.getUsername());
			ps.setString(2, user.getPassword());
			rs = ps.executeQuery();
			if(rs.next()){
				//如果能进来。说明账号密码输入正确
				return user;
			}
			return null;
			
		} catch (SQLException e) {
			e.printStackTrace();
			throw new RuntimeException("添加失败！");
		}
	}

}
