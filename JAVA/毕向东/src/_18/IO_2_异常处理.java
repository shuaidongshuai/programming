package _18;

import java.io.*;

public class IO_2_异常处理 {
	public static void main(String[] args) {
		FileWriter fw = null;
		try {
			fw = new FileWriter("E:\\programming\\JAVA\\垃圾文件\\io_1.txt");
			fw.write("dong");
		} catch (IOException e) {
			System.out.println(e.toString());
		} finally{
			if(fw!=null)
			try {
				fw.close();
			} catch (IOException e2) {
				System.out.println(e2.toString());
			}
		}
	}
}
