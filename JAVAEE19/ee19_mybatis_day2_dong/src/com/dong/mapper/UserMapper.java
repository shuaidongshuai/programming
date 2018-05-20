package com.dong.mapper;

import java.util.List;

import com.dong.po.OrdersExt;

public interface UserMapper {
	//延迟加载
	public void findUserById();
	public List<OrdersExt> findOrderAndUserLazyLoading();
}
