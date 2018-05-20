package com.dong.aspect;

import org.aspectj.lang.JoinPoint;
import org.aspectj.lang.ProceedingJoinPoint;
import org.aspectj.lang.annotation.After;
import org.aspectj.lang.annotation.AfterReturning;
import org.aspectj.lang.annotation.AfterThrowing;
import org.aspectj.lang.annotation.Around;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Before;
import org.aspectj.lang.annotation.Pointcut;
import org.junit.experimental.theories.Theory;
import org.springframework.stereotype.Component;

@Component
@Aspect
public class MyAspect {
	
	//声明公共切入点
	@Pointcut("execution(* com.dong.aspect.UserServiceImpl.*(..))")
	public void myPointCut(){
	}
	
	//是有一个参数的，只是默认为空了
//	@Before(value="myPointCut()")
	public void myBefore(){
		System.out.println("前置通知");
	}
	
//	@AfterReturning(value="myPointCut()", returning="ret_dong")
	public void myAfterReturning(JoinPoint joinPoint, Object ret_dong){
		System.out.println("后置通知" + joinPoint.getSignature().getName() + "  " + ret_dong);
	}
	
//	@Around(value="myPointCut()")
	public Object myAround(ProceedingJoinPoint joinPoint) throws Throwable{
		System.out.println("前");
		//手动执行目标方法
		Object obj = joinPoint.proceed();
		System.out.println("后");
		return obj;
	}
	
//	@AfterThrowing(value="myPointCut()", throwing="e")
	public void myAfterThrowing(JoinPoint joinPoint,Throwable e){
		System.out.println(e.getMessage());
	}
	
	@After("myPointCut()")
	public void myAfter(JoinPoint joinPoint){
		System.out.println("最终通知");
	}
}
