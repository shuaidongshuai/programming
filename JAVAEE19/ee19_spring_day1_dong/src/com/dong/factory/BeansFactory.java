package com.dong.factory;

public class BeansFactory {
	
	public static UserService createUserService(){
		return new UserServiceImpl();
	}
	
	public UserService createUserService2(){
		return new UserServiceImpl();
	}
}
