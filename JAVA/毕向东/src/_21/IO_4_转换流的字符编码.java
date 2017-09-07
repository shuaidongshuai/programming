package _21;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;

public class IO_4_转换流的字符编码 {
	public static void main(String[] args) throws IOException {
		OutputStreamWriter osw = new OutputStreamWriter(new FileOutputStream("E:\\programming\\JAVA\\垃圾文件\\gbk.txt"),"GBK");
		osw.write("你好");
		osw.close();
		
		OutputStreamWriter osw2 = new OutputStreamWriter(new FileOutputStream("E:\\programming\\JAVA\\垃圾文件\\UTF-8.txt"),"UTF-8");
		osw2.write("你好");
		osw2.close();
	}
}
