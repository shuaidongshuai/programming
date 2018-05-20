package com.dong.dbcp;

import java.util.List;

import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.RowMapper;
import org.springframework.jdbc.core.simple.ParameterizedBeanPropertyRowMapper;

import com.dong.domain.User;

public class UserDao {
	private JdbcTemplate jdbcTemplate;

	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}
	/*
	 * ParameterizedBeanPropertyRowMapper会把传进去的类和行数据关联起来
	 * 注意：User必须要有空构造函数
	 */
	public List<User> findAll(){
		String sql = "select * from t_user";
		return jdbcTemplate.query(sql, ParameterizedBeanPropertyRowMapper.newInstance(User.class));
	}
}
