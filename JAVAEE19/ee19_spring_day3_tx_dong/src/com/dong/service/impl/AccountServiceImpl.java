package com.dong.service.impl;

import org.springframework.transaction.annotation.Isolation;
import org.springframework.transaction.annotation.Propagation;
import org.springframework.transaction.annotation.Transactional;

import com.dong.dao.AccountDao;
import com.dong.service.AccountService;

public class AccountServiceImpl implements AccountService {
	private AccountDao accountDao;
	public void setAccountDao(AccountDao accountDao) {
		this.accountDao = accountDao;
	}
	
	@Transactional(propagation=Propagation.REQUIRED, isolation=Isolation.DEFAULT)
	public void transfer(String outter, String inner, int money) {
		accountDao.out(outter, money);
		int i = 1 / 0; //断电
		accountDao.in(inner, money);
	}

}
