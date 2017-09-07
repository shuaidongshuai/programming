package com.dong.entity;

public class Beauty {
	private String name;
	private String price;
	private int num;
	
	
	public Beauty(String name, String price, int num) {
		super();
		this.name = name;
		this.price = price;
		this.num = num;
	}
	@Override
	public String toString() {
		return "Beauty [name=" + name + ", price=" + price + ", num=" + num
				+ "]";
	}
	public int getNum() {
		return num;
	}
	public void setNum(int num) {
		this.num = num;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getPrice() {
		return price;
	}
	public void setPrice(String price) {
		this.price = price;
	}
}
