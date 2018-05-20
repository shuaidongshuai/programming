package com.dong.entity;

import java.util.Date;


public class dbUser {
	private int id;
	private String name;
	private int score;
	private Date time;
	public int getId() {
		return id;
	}
	@Override
	public String toString() {
		return "dbUser [id=" + id + ", name=" + name + ", score=" + score
				+ ", time=" + time + "]";
	}
	public Date getTime() {
		return time;
	}
	public void setTime(Date time) {
		this.time = time;
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
	
}
