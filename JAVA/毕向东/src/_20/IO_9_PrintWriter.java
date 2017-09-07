package _20;

import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
/*
 * PrintStream
 * 构造函数可以接受的类型
 * File 对象
 * 字符串路径
 * 字节输出流OutputStream
 * 
 * PrintWriter
 * File 对象
 * 字符串路径
 * 字节输出流OutputStream
 * 字符输出流通Writer 
 */
public class IO_9_PrintWriter {
	public static void main(String[] args) throws IOException {
		BufferedReader bufr = new BufferedReader(new InputStreamReader(System.in));
//		PrintWriter out = new PrintWriter(System.out,true);//true在这里等价于下面的    out.flush();   每输入一行就清空缓冲区
//		PrintWriter out = new PrintWriter("E:\\programming\\JAVA\\垃圾文件\\1.txt");
		PrintWriter out = new PrintWriter(new FileWriter("E:\\programming\\JAVA\\垃圾文件\\1.txt"));
		
		String line;
		while((line = bufr.readLine())!=null){
			out.println(line);
//			out.flush();
		}
		
		bufr.close();
		out.close();
		
	}
}
