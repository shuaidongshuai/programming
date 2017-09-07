package _19;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

/*
 * 通过缓冲区
 * 
 */
public class IO_4_复制mp3 {
	public static void main(String[] args) throws IOException {
		long start = System.currentTimeMillis();
		copy();
		long end = System.currentTimeMillis();
		System.out.println("用来"+(end-start)+"毫秒");
		
	}
	public static void copy() throws IOException {
		BufferedInputStream bufis = new BufferedInputStream(new FileInputStream("D:\\音乐\\Cincinnati Pops Orchestra - Themes from Silverado.mp3"));
		BufferedOutputStream bufos = new BufferedOutputStream(new FileOutputStream("C:\\Users\\37916\\Desktop\\1.mp4"));
		
		int Byte = 0;
		while((Byte = bufis.read())!= -1){//注意这里是读取一个字节，返回的是这个字节。。转化为10进制   后  再与   0xff  进行与运算
			bufos.write(Byte);//注意这里是写一个字节。只看Byte这个十进制的  低8位（把十进制强转为byte）。其实传给他的数据也只有低8位有效，其余位全为0
		}
		//为什么要进行转化为10进制，然后又转化为byte型？
		//答：为了有结束符，，结束符是-1   那么很有可能传过来的数据(二进制)就是11111111  那么就不能区别，到底哪个是结束符
		//也就是说   避免和结束符冲突，，为了让11111111这种二进制数据可以进行传递
		bufis.close();
		bufos.close();
	}
}
