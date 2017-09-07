package com.dong.entity;

import java.util.Arrays;

//在实体类中的字段要与表单中的name名一致。约定优于编码 
public class User {
	private String username;
	private String pwd;
	private String sex;
	private String[] hobby;
	private String city;
	public String getUsername() {
		return username;
	}
	public void setUsername(String username) {
		this.username = username;
	}
	public String getPwd() {
		return pwd;
	}
	public void setPwd(String pwd) {
		this.pwd = pwd;
	}
	public String getSex() {
		return sex;
	}
	public void setSex(String sex) {
		this.sex = sex;
	}
	public String[] getHobby() {
		return hobby;
	}
	public void setHobby(String[] hobby) {
		this.hobby = hobby;
	}
	public String getCity() {
		return city;
	}
	public void setCity(String city) {
		this.city = city;
	}
	@Override
	public String toString() {
		return "User [username=" + username + ", pwd=" + pwd + ", sex=" + sex
				+ ", hobby=" + Arrays.toString(hobby) + ", city=" + city + "]";
	}
	
}
