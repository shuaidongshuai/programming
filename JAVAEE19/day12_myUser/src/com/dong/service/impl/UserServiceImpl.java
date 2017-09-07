package com.dong.service.impl;

import com.dong.dao.UserDao;
import com.dong.dao.impl.UserDaoImpl;
import com.dong.domain.User;
import com.dong.service.UserService;

public class UserServiceImpl implements UserService{
	UserDao userDao = new UserDaoImpl();

	public void register(User user) {
		userDao.addUser(user);
	}

	public User login(User user) {
		return userDao.findUser(user);
	}
	
	
	
}
