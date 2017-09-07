package _20;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.SequenceInputStream;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.Iterator;
import java.util.Vector;

public class IO_11_切割文件 {
	public static void main(String[] args) throws IOException {
		splitFile();
		hebing();
	}
	
	public static void splitFile() throws IOException{
		FileInputStream fis = new FileInputStream("E:\\programming\\JAVA\\垃圾文件\\东.jpg");
		FileOutputStream fos = null;
		
		byte[] buf = new byte[1024*100];//每份100kb
		int len = 0;
		int count = 1;
		while((len = fis.read(buf))!= -1 ){
			fos = new FileOutputStream("E:\\programming\\JAVA\\垃圾文件\\东"+(count++)+".part");
			fos.write(buf,0,len);
			fos.close();
		}
		fis.close();
	}
	//用ArrayList来合并
	public static void hebing() throws IOException{
		ArrayList<FileInputStream> al = new ArrayList<FileInputStream>();
		for(int i=1;i<5;i++){
			al.add(new FileInputStream("E:\\programming\\JAVA\\垃圾文件\\东"+i+".part"));
		}
		
		final Iterator<FileInputStream> it = al.iterator();//获取迭代器
		//为什么要下面这一步？因为：SequenceInputStream(Enumeration<? extends InputStream> e) 只接受Enumeration接口方法
		Enumeration<FileInputStream> en = new Enumeration<FileInputStream>(){//这是一个内部类    然后复写接口方法
			public boolean hasMoreElements() {
				return it.hasNext();
			}
			public FileInputStream nextElement() {
				return it.next();
			}
		};
		
		SequenceInputStream sis = new SequenceInputStream(en);
		
		File f = new File("E:\\programming\\JAVA\\垃圾文件\\东5.jpg");
		FileOutputStream fos = new FileOutputStream(f);
		
		byte[] buf = new byte[1024];
		int len = 0;
		while((len = sis.read(buf))!=-1){
			fos.write(buf,0,len);
		}
		fos.close();
		sis.close();
//		Vector<FileInputStream> v = new Vector<FileInputStream>();
//		v.add(new FileInputStream("E:\\programming\\JAVA\\垃圾文件\\东1.part"));
//		v.add(new FileInputStream("E:\\programming\\JAVA\\垃圾文件\\东2.part"));
//		v.add(new FileInputStream("E:\\programming\\JAVA\\垃圾文件\\东3.part"));
//		v.add(new FileInputStream("E:\\programming\\JAVA\\垃圾文件\\东4.part"));
//		
//		Enumeration<FileInputStream> en = v.elements();
//		//SequenceInputStream 表示其他输入流的逻辑串联。它从输入流的有序集合开始，并从第一个输入流开始读取，直到到达文件末尾，
//		//接着从第二个输入流读取，依次类推，直到到达包含的最后一个输入流的文件末尾为止。 
//		SequenceInputStream sis = new SequenceInputStream(en);
//		
//		FileOutputStream fos = new FileOutputStream("E:\\programming\\JAVA\\垃圾文件\\东5.bmp");
//		
//		byte[] buf = new byte[1024*100];
//		int len = 0;
//		while((len = sis.read(buf))!=-1){
//			fos.write(buf,0,len);
//		}
//		fos.close();
//		sis.close();
	}
}
