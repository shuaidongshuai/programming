package com.dong.domain;

import java.io.Serializable;
import java.util.Date;
/**
 * UserBean
 * @author ☆东★
 *
 */
public class User implements Serializable{//Serializable是一个空接口，没有什么具体内容，它的目的只是简单的标识一个类的对象可以被序列化。
	private int id;
	private String username;
	private String password;
	private String email;
	private Date birthday;
	
	public int getId() {
		return id;
	}
	public void setId(int id) {
		this.id = id;
	}
	public String getUsername() {
		return username;
	}
	public void setUsername(String username) {
		this.username = username;
	}
	public String getPassword() {
		return password;
	}
	public void setPassword(String password) {
		this.password = password;
	}
	public String getEmail() {
		return email;
	}
	public void setEmail(String email) {
		this.email = email;
	}
	public Date getBirthday() {
		return birthday;
	}
	public void setBirthday(Date birthday) {
		this.birthday = birthday;
	}
}
