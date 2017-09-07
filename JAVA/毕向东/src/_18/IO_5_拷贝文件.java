package _18;

import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class IO_5_拷贝文件 {
	public static void main(String[] args) {
		FileReader fr = null;
		FileWriter fw = null;
		char[] buf = new char[1];
		int num = 0;
		
		try{
			fr = new FileReader("E:\\programming\\JAVA\\垃圾文件\\io_1.txt");
			fw = new FileWriter("E:\\programming\\JAVA\\垃圾文件\\io_2.txt");
			while((num = fr.read(buf))!=-1){
				fw.write(buf,0,num);
			}
		} catch(IOException e){
			System.out.println("文件读取错误");
		} finally{
			if(fr!=null)
				try {
					fr.close();
				} catch (IOException e2) {
					System.out.println("文件关闭错误");
				}
			if(fw!=null)
				try {
					fw.close();
				} catch (Exception e2) {
					System.out.println("文件关闭错误");
				}
		}
	}
}
