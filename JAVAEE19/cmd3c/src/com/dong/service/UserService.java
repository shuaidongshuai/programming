package com.dong.service;

import com.dong.domain.User;

public interface UserService {
	
	/**
	 * 注册
	 * @param user
	 */
	public void register(User user);
	
	/**
	 * 看用户账号密码是否正确，如果正确，返回传进来的user，否则返回null
	 * @param uesr
	 * @return
	 */
	public User login(User uesr);
}
