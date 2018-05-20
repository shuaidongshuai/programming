package com.dong.dao;
/**
 * 汇款、收款
 * @author ☆东★
 *
 */
public interface AccountDao {
	public void out(String outter, Integer money); 
	public void in(String inner, Integer money); 
}
