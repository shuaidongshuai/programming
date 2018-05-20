package com.dong.c3p0;

import org.springframework.jdbc.core.JdbcTemplate;

import com.dong.domain.User;

public class UserDao {
	private JdbcTemplate jdbcTemplate;

	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}
	
	public int update(User user){
		String sql = "update t_user set username=?,password=? where id=?";
		Object[] args = {user.getUsername(),user.getPassword(),user.getId()};
		return jdbcTemplate.update(sql, args);
	}
}
