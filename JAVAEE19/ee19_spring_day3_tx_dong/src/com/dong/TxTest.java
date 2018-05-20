package com.dong;

import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

import com.dong.service.AccountService;
import com.dong.service.impl.AccountServiceImpl;

public class TxTest {
	public static void main(String[] args) {
		String xmlPath = "applicationContext.xml";
		ApplicationContext applicationContext = new ClassPathXmlApplicationContext(xmlPath);
		AccountService accountService = (AccountService) applicationContext.getBean("accountService");
		accountService.transfer("帅东", "周冬雨", 1000);
	}
}
