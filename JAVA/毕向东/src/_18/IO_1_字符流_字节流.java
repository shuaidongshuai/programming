package _18;
/*
 * 字符流两个基类：
 * InputStream	OutputStream
 * 
 * 字符流两个基类：
 * Reader Write
 * 
 * 需求：在硬盘上，创建一个文件，并写入一段文字
 * 
 * 找到一个专门用于操作文件的Writer子类对象。FileWirter。后缀名是父类名，前缀名是对象的功能
 */
import java.io.*;
public class IO_1_字符流_字节流 {
	public static void main(String[] args) throws IOException {
		//创建一个FileWriter对象。该对象一被初始化就必须明确备操作的文件
		FileWriter fw = new FileWriter("E:\\programming\\JAVA\\垃圾文件\\io_1.txt");//注意加反斜杠
		//void write(String str)  写入字符串。(写入流缓冲区中
		fw.write("dong");
		//刷新该流对象中的缓冲区中的数据，将数据刷到目的地中
		fw.flush();
		
		fw.write("1234");
		
//		fw.flush();
		fw.close();//关闭也刷新
		
		
        
		
	}
}
