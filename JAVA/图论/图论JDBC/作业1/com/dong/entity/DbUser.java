package com.dong.entity;

public class DbUser {
	private String name;
	private String sex;
	private String date;
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getSex() {
		return sex;
	}
	public void setSex(String sex) {
		this.sex = sex;
	}
	public String getDate() {
		return date;
	}
	public void setDate(String date) {
		this.date = date;
	}
	@Override
	public String toString() {
		return "»¶Ó­Äã\n"+ name + "\t" + sex + "\t" + date + "";
	}
	
}
