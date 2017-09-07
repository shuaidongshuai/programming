package _21;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.CharArrayReader;
import java.io.CharArrayWriter;
import java.io.IOException;

public class IO_3_byteArray {
	public static void main1(String[] args) {
		String s = "hello_dong";
		ByteArrayInputStream bais = new ByteArrayInputStream(s.getBytes()); 
		ByteArrayOutputStream baos = new ByteArrayOutputStream();
		
		int len = 0;
		while((len = bais.read())!=-1){
			baos.write(len);
		}
		System.out.println(baos.size());
		System.out.println(baos.toString());
		
		String ss = new String(baos.toByteArray());
		System.out.println(ss);
	}
	public static void main(String[] args) throws IOException {
		String s = "dong";
		CharArrayReader car = new CharArrayReader(s.toCharArray());
		CharArrayWriter caw = new CharArrayWriter();
		int len = 0;
		while((len = car.read())!=-1){
			caw.write(len);
		}
		System.out.println(caw.size());
		System.out.println(caw.toString());
		
	}
}
