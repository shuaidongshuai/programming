package com.dong.properties;

import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.simple.ParameterizedBeanPropertyRowMapper;
import org.springframework.jdbc.core.support.JdbcDaoSupport;

import com.dong.domain.User;

public class UserDao extends JdbcDaoSupport{
	
	public User getById(int id){
		String sql = "select * from t_user where id=?";
		return getJdbcTemplate().queryForObject(sql, ParameterizedBeanPropertyRowMapper.newInstance(User.class), id);
	}
}
