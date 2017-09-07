package _19;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
/*
 * 1，明确源和目的
 * 		源，输入流。InputStream Reader
 * 		目的，输出流。OutputStream Reader
 * 2，操作的数据是否是纯文本
 * 		是，字符流
 * 		否，字节流
 * 3，当体系明确后，再明确要使用那个具体的对象
 * 		通过设备来进行区分
 * 		源设备：内存，硬盘，键盘
 * 		目的设备：内存，银盘，控制台
 * 
 */
public class IO_6_读取转换流 {
	public static void main(String[] args) throws IOException {
		/*
		//获取键盘录入对象
		InputStream in = System.in;
		
		OutputStream out = System.out;
		//OutputStreamWriter 是字符流通向字节流的桥梁
		OutputStreamWriter osw = new OutputStreamWriter(out);
		
		//InputStreamReader是字节流通向字符流的桥梁
		InputStreamReader isr = new InputStreamReader(in);*/
		
		//上面几句话，可以变得更简单
		InputStreamReader isr = new InputStreamReader(System.in);
		OutputStreamWriter osw = new OutputStreamWriter(System.out);
		
		//使用缓冲区
		BufferedReader bufr = new BufferedReader(isr);
		String line = null;
		while((line = bufr.readLine())!=null){
			osw.write(line.toUpperCase()+"\r\n");
			osw.flush();
		}
		bufr.close();
	}
	public static void main1(String[] args) throws IOException {
		//键盘输入的最常见写法
		
		//从键盘录入
//		BufferedReader bufr = new BufferedReader(new InputStreamReader(System.in));
		//从文件录入
		BufferedReader bufr = new BufferedReader(new InputStreamReader(new FileInputStream("E:\\programming\\JAVA\\垃圾文件\\io_1.txt")));
		
		
		//输出到控制台
//		BufferedWriter bufw = new BufferedWriter(new OutputStreamWriter(System.out));
		//输出到文件中
//		BufferedWriter bufw = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("E:\\programming\\JAVA\\垃圾文件\\io_1.txt")));
		
		BufferedWriter bufw = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("E:\\programming\\JAVA\\垃圾文件\\io_2.txt"),"GBK"));
//		BufferedWriter bufw = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("E:\\programming\\JAVA\\垃圾文件\\io_3.txt"),"UTF-8"));
		String line;
		while((line=bufr.readLine())!=null){
			bufw.write(line);
			bufw.newLine();
			bufw.flush();
		}
	}
}
