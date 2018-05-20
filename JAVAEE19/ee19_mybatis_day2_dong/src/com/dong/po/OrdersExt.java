package com.dong.po;

import java.util.List;

public class OrdersExt extends Orders{
	private String username;
	private String address;
	//用户信息
    private User user;
    //订单详情
    private List<Orderdetail> orderdetailList;
    
	public String getUsername() {
		return username;
	}
	public void setUsername(String username) {
		this.username = username;
	}
	public String getAddress() {
		return address;
	}
	public void setAddress(String address) {
		this.address = address;
	}
	public User getUser() {
		return user;
	}
	public void setUser(User user) {
		this.user = user;
	}
	public List<Orderdetail> getOrderdetail() {
		return orderdetailList;
	}
	public void setOrderdetail(List<Orderdetail> orderdetail) {
		this.orderdetailList = orderdetail;
	}
	@Override
	public String toString() {
		return super.toString()+"OrdersExt [username=" + username + ", address=" + address
				+ ", user=" + user + ", orderdetail=" + orderdetailList + "]";
	}
	
}
