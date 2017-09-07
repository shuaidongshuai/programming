package com.dong.client;

import java.util.Iterator;
import java.util.List;

import com.dong.io.ReadText;

public class Test {
	public static void main(String[] args) {
		ReadText readText = new ReadText();
		List list = readText.read("C:\\Users\\37916\\Desktop\\新建文件夹\\female.txt");
//		for(int i = 0;i<list.size();i++){
//			System.out.println(list.get(i));
//		}
		String str = (String) list.get(1);
		String[] split = str.split(",");
		for(int i = 0;i<split.length;i++){
			System.out.println(split[i]);
		}
	}
}
