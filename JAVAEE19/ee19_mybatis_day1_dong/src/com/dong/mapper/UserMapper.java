package com.dong.mapper;

import java.util.List;

import com.dong.po.User;

public interface UserMapper {
	public User findUserById(int id) throws Exception;
	public List<User> findUsersByName(String name) throws Exception;
	public void insertUser(User user) throws Exception;
}
