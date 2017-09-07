package _20;

import java.io.File;
import java.io.IOException;

/*
 * File类
 * 1，创建
 * 		boolean createNewFile();在指定位置创建文件，如果该文件已经存在，则不创建，返回false
 * 								和输出流不一样，输出流对象一建立就创建文件
 * 2，删除
 * 
 * 3，判断
 * 		boolean exists();	文件是否存在
 * 		isFile();
 * 		isDirection();
 * 		isHidden();	隐藏
 * 4，获取信息
 * 		getName();
 * 		getPath();
 * 		getParent(); 
 * 
 * 
 * 
 */
public class IO_2 {
	public static void main1(String[] args) throws IOException {
		File f = new File("E:\\programming\\JAVA\\垃圾文件\\1.txt");
		//创建
		System.out.println(f.createNewFile());
		//删除
//		System.out.println(f.delete());
		
		//在程序退出时，自动删除文件。。避免出现异常删不掉
		f.deleteOnExit();
		
		for(int i=0;i<300000;i++){//为了看效果
			System.out.println(".");
		}
	}
	public static void main(String[] args) {
		//创建文件夹
		File dir = new File("E:\\programming\\JAVA\\垃圾文件\\1\\1\\2\\3\\4\\5");
		System.out.println(dir.mkdir());//最多创建两级目录
		System.out.println(dir.mkdirs());//可以创建多级目录
		
		
		File f = new File("E:\\programming\\JAVA\\垃圾文件\\1.txt");
		System.out.println(f.exists());
	}
}
