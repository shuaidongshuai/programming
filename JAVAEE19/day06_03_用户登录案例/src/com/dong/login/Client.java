package com.dong.login;

import java.util.Scanner;

import com.dong.entity.dbUser;

public class Client {
	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		System.out.println("请输入用户名：");
		String name = input.nextLine();
		System.out.println("请输入密码：");
		String pwd = input.nextLine();
		
		ServerUp serverUp = new ServerUp();
		dbUser u = serverUp.findUser(name, pwd);
		if(u!=null){
			System.out.println(u);
		}else{
			System.out.println("错误");
		}
	}
}
