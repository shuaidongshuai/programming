package com.dong.annotation;

import org.springframework.stereotype.Component;

@Component("userService")
public class UserServiceImpl implements UserService {

	@Override
	public void addUser() {
		System.out.println("com.dong.annotation add user");
	}

}
