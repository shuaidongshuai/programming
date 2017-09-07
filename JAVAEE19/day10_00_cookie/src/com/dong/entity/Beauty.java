package com.dong.entity;

public class Beauty {
	private String name;
	private String price;
	
	public Beauty(String name, String price) {
		super();
		this.name = name;
		this.price = price;
	}
	@Override
	public String toString() {
		return "Beauty [ name=" + name + ", price=" + price + "]";
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
