package com.dong.po;

import java.sql.Date;

public class User {
	private int id;
	private String name;
	private int score;
	private Date time;
	private String password;
	
	//默认构造不能丢
	public User() {
		super();
	}
	public User(String name, int score, String password) {
		super();
		this.name = name;
		this.score = score;
		this.password = password;
	}
	public int getId() {
		return id;
	}
	public void setId(int id) {
		this.id = id;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public int getScore() {
		return score;
	}
	public void setScore(int score) {
		this.score = score;
	}
	public Date getTime() {
		return time;
	}
	public void setTime(Date time) {
		this.time = time;
	}
	public String getPassword() {
		return password;
	}
	public void setPassword(String password) {
		this.password = password;
	}
	@Override
	public String toString() {
		return "User [id=" + id + ", name=" + name + ", score=" + score
				+ ", time=" + time + ", password=" + password + "]";
	}
	
}
