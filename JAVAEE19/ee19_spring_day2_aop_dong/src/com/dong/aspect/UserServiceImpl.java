package com.dong.aspect;

import org.springframework.stereotype.Service;

@Service("UserService")
public class UserServiceImpl implements UserService {

	@Override
	public void addUser() {
		System.out.println("addUser");
	}

	@Override
	public String updateUser() {
		System.out.println("updateUser");
//		int a = 1 / 0;
		return "hello";
	}

	@Override
	public void deleteUser() {
		System.out.println("deleteUser");
	}

}
