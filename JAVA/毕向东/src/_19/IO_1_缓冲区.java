package _19;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class IO_1_缓冲区 {
	public static void main(String[] args) throws IOException {
		//创建一个字符写入流  对象
		FileReader fr = new FileReader("E:\\programming\\JAVA\\垃圾文件\\io_1.txt");
		FileWriter fw = new FileWriter("E:\\programming\\JAVA\\垃圾文件\\io_2.txt");
		
		//将对象作为参数传递给缓冲区的构造函数
		BufferedWriter bufw = new BufferedWriter(fw);
		//读取
		BufferedReader bufr = new BufferedReader(fr);
		
		
		String line = null;
		while((line = bufr.readLine())!=null){//包含该行内容的字符串，不包含任何行终止符，如果已到达流末尾，则返回 null 
			bufw.write(line);
			bufw.newLine();
			bufw.flush();	
		}
		
	}
}
