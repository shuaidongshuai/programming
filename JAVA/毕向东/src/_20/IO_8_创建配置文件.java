package _20;

import java.io.*;
import java.util.*;

public class IO_8_创建配置文件 {
	public static void main(String[] args) throws IOException {
		File file = new File("E:\\programming\\JAVA\\垃圾文件\\count.ini");
		Properties prop = new Properties();
		
		if(!file.exists())//如果文件不存在
			file.createNewFile();
		
		FileReader fr = new FileReader(file);
		
		prop.load(fr);//按简单的面向行的格式从输入字符流中读取属性列表（键和元素对）。     【  加载  （读取以前的数据）】
		
		int count = 0;
		String value = prop.getProperty("time");//获取time（键值）的value
		
		if(value!=null){
			//static int parseInt(String s, int radix)使用第二个参数指定的基数，将字符串参数解析为有符号的整数。  
	         count = Integer.parseInt(value);
	         if(count>4){
	        	 System.out.println("这款软件您使用的次数到了");
	        	 System.exit(0);
	         }
		}
		System.out.println("欢迎使用");
		count ++;
		prop.setProperty("time", count+"");
		
		FileWriter fw = new FileWriter(file);
		
		prop.store(fw, "Welcome to My init");//把键值对写入文件中(保存)
		
		fw.close();
		fr.close();
	}
}
