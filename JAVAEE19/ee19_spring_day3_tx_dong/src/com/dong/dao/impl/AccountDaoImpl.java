package com.dong.dao.impl;

import org.springframework.jdbc.core.support.JdbcDaoSupport;

import com.dong.dao.AccountDao;

public class AccountDaoImpl extends JdbcDaoSupport implements AccountDao {

	public void out(String outter, Integer money) {
		String sql = "update account set money = money - ? where username = ?";
		this.getJdbcTemplate().update(sql, money, outter);
	}

	public void in(String inner, Integer money) {
		String sql = "update account set money = money + ? where username = ?";
		this.getJdbcTemplate().update(sql, money, inner);
	}

}
