package _18;

import java.util.Calendar;
import java.util.Date;
import java.util.Scanner;

public class 日期之间的计算 {
	public static void main1(String[] args) {
		//获取某一年的天数
		Calendar c = Calendar.getInstance();
		Scanner sc = new Scanner(System.in);
		int year = sc.nextInt();
		c.set(year,11,31);//月份是从0开始，，今年的12月31日
		System.out.println(c.get(Calendar.DAY_OF_YEAR));//返回今年开始到12月31日  的天数
	}
	public static void main(String[] args) {
		//获取某一年的2月份天数
		Calendar c = Calendar.getInstance();
		Scanner sc = new Scanner(System.in);
		int year = sc.nextInt();
		c.set(year, 2,1);//设置日期为3月1日
		c.add(Calendar.DAY_OF_MONTH, -1);//当前日期减一天
		System.out.println(c.get(Calendar.DAY_OF_MONTH));//获取减去后的这个月天数
		
	}
	
	//从键盘输入
	public static void main2(String[] args) {
		  Scanner sc = new Scanner(System.in); 
		  
		  
		    System.out.println("ScannerTest, Please Enter Name:"); 
		    String name = sc.nextLine();  //读取字符串型输入 
		    
		    System.out.println("ScannerTest, Please Enter Age:"); 
		    int age = sc.nextInt();    //读取整型输入 
		    
		    System.out.println("ScannerTest, Please Enter Salary:"); 
		    float salary = sc.nextFloat(); //读取float型输入 
		    
		    
		    System.out.println("Your Information is as below:"); 
		    System.out.println("Name:" + name +"\n" + "Age:"+age + "\n"+"Salary:"+salary); 
	}
}
