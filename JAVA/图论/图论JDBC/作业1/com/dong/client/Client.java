package com.dong.client;

import java.io.IOException;
import java.util.Scanner;

import com.dong.Server.Server;

public class Client {
	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		while(true)
		{
			System.out.println("登录请按1\t注册请按2\t退出请按3");
			int b = input.nextInt();
			if(3 == b){
				break;
			}
			
			System.out.println("请输入用户名：");
			String name = input.next();
			System.out.println("请输入密码（至多10位）：");
			String pwd = input.next();
			if(1 == b){
				new Server().login(name, pwd);
			}else if(2 == b){
				System.out.println("请输入性别(man or woman)：");
				String sex = input.next();
				new Server().register(name, pwd, sex);
			}
		}
		System.out.println("正常退出！");
	}
}
