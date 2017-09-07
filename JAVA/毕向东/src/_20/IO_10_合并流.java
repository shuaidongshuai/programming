package _20;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.SequenceInputStream;
import java.util.Enumeration;
import java.util.Vector;

public class IO_10_合并流 {
	public static void main(String[] args) throws IOException {
		Vector<FileInputStream> v = new Vector<FileInputStream>();
		v.add(new FileInputStream("E:\\programming\\JAVA\\垃圾文件\\东1.part"));
		v.add(new FileInputStream("E:\\programming\\JAVA\\垃圾文件\\东2.part"));
		v.add(new FileInputStream("E:\\programming\\JAVA\\垃圾文件\\东3.part"));
		v.add(new FileInputStream("E:\\programming\\JAVA\\垃圾文件\\东4.part"));
		
		Enumeration<FileInputStream> en = v.elements();
		//SequenceInputStream 表示其他输入流的逻辑串联。它从输入流的有序集合开始，并从第一个输入流开始读取，直到到达文件末尾，
		//接着从第二个输入流读取，依次类推，直到到达包含的最后一个输入流的文件末尾为止。 
		SequenceInputStream sis = new SequenceInputStream(en);
		
		FileOutputStream fos = new FileOutputStream("E:\\programming\\JAVA\\垃圾文件\\东5.bmp");
		
		byte[] buf = new byte[1024*100];
		int len = 0;
		while((len = sis.read(buf))!=-1){
			fos.write(buf,0,len);
		}
		fos.close();
		sis.close();
	}
}
