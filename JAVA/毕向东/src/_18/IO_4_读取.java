package _18;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class IO_4_读取 {
	public static void main(String[] args) throws IOException {
		//要保证文件存在
		FileReader fr = new FileReader("E:\\programming\\JAVA\\垃圾文件\\io_1.txt");
		//调用读取流对象的read方法。read()一个第一个字符，而且会自动往下读、读到末尾返回-1
		//第一种 方式
//		int ch;
//		while((ch = fr.read())!=-1)
//			System.out.println((char)ch);
		
		//第二种
		//定义一个字符数组，用于存储读到的字符
		char[] buf = new char[1024];
		int num;
		while((num = fr.read(buf))!=-1){
			System.out.print(new String(buf,0,num));
		}
		
	}
}
