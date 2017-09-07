package _19;
/*
 * 字节流
 * InputStream读   OutputStream写
 * 
 */
import java.io.*;
public class IO_2_字节流 {
	public static void main(String[] args) throws IOException {
		writeFile();
		readFile();
	}
	public static void writeFile() throws IOException{
		FileOutputStream fos = new FileOutputStream("E:\\programming\\JAVA\\垃圾文件\\io_1.txt");
		
		fos.write("abcd".getBytes());
		fos.write("2134".getBytes());//是以追加的方式写入
	}
	public static void readFile() throws IOException{
		FileInputStream fis = new FileInputStream("E:\\programming\\JAVA\\垃圾文件\\io_1.txt");
		
		byte[] buf = new byte[1024];
		int len = 0;
		while((len = fis.read(buf))!=-1){
			System.out.println(new String(buf,0,len));
		}
		fis.close();
	}
	
}
