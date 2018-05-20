package com.dong.aop;

import org.aopalliance.intercept.MethodInterceptor;
import org.aopalliance.intercept.MethodInvocation;

public class MyAspect implements MethodInterceptor{

	@Override
	public Object invoke(MethodInvocation mi) throws Throwable {
		System.out.println("开启事务");
		Object obj = mi.proceed();
		System.out.println("关闭事务");
		return obj;
	}
	
}
