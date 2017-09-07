package _18;

import java.io.FileWriter;
import java.io.IOException;

public class IO_3_文件续写 {
	public static void main(String[] args) throws IOException {
		FileWriter fw = new FileWriter("E:\\programming\\JAVA\\垃圾文件\\io_1.txt",true);//加上一个true就是以追加的方式写入。不重新创建文件
		fw.write("\r\n1234");
		fw.write("\r\n1234");
		fw.write("\r\n1234");
		fw.write("\r\n1234");
		fw.close();
		
	}
}
