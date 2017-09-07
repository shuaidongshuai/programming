package _20;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class IO_12_切割电影 {
	public static void main(String[] args) throws IOException {
		splitFile();
	}
	public static void splitFile() throws IOException{
		FileInputStream fis = new FileInputStream("E:\\study_materials\\JAVA\\毕向东\\05\\黑马程序员_毕向东_Java基础视频教程第05天-03-面向对象(类与对象的关系).avi");
		FileOutputStream fos = null;
		
		byte[] buf = new byte[1024*1024];
		int len;
		for(int i=0;i<3;i++){//大概判断要几个文件来装
			fos = new FileOutputStream("E:\\programming\\JAVA\\垃圾文件\\东"+i+".part");
			for(int j=0;j<20;j++){//每一份碎片文件循环写入50次，每次写入的是1M。。加起来就是   一个碎片文件50M
				len = fis.read(buf);
				if(len == -1) break;//没有这句话  虽然结果一样，但是老师会报错。。原因就是 len != -1  如果没有这句话     write 就会写入  0,-1这样的值
				fos.write(buf,0,len);
			}
			fos.close();
		}
		fis.close();
	}
}
