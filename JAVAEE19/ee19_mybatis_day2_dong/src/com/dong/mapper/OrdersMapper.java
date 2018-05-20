package com.dong.mapper;

import java.util.List;

import com.dong.po.OrdersExt;

public interface OrdersMapper {
	//Orders - User 一对一
	public List<OrdersExt> findOrdersUser();
	//Orders User - Orderdetail 一对多
	public List<OrdersExt> findOrdersUserOrderdetail();
}
