package com.dong.domain;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class UserCustom {
	User user;
	
	private List<User> userList;
	
	private Map<String,Object> maps;
	
	public UserCustom() {
		super();
//		userList = new ArrayList<User>();
//		maps = new HashMap<String, Object>();
	}

	public List<User> getUserList() {
		return userList;
	}

	public void setUserList(List<User> userList) {
		this.userList = userList;
	}

	public Map<String, Object> getMaps() {
		return maps;
	}

	public void setMaps(Map<String, Object> maps) {
		this.maps = maps;
	}

	public User getUser() {
		return user;
	}

	public void setUser(User user) {
		this.user = user;
	}

	@Override
	public String toString() {
		return "UserCustom [user=" + user + ", userList=" + userList
				+ ", maps=" + maps + "]";
	}
}
