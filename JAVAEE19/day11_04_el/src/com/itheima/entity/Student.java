package com.itheima.entity;

public class Student {
	private String name;
	private String password;
	private City city = new City();
	
	
	
	public City getCity() {
		return city;
	}
	public void setCity(City city) {
		this.city = city;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getPassword() {
		return password;
	}
	public void setPassword(String password) {
		this.password = password;
	}
	
	public void show(String name){
		this.name = name;
	}
	
}
