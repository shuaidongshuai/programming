package com.dong.user;

public class User {
	public String name;
	public String score;
	public User() {
		super();
	}
	public User(String name, String score) {
		super();
		this.name = name;
		this.score = score;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getScore() {
		return score;
	}
	public void setScore(String score) {
		this.score = score;
	}
	
}
