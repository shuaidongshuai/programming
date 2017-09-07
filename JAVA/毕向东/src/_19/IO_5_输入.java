package _19;

import java.io.IOException;
import java.io.InputStream;

public class IO_5_ ‰»Î {
	public static void main(String[] args) throws IOException {
		InputStream in = System.in;
		
		System.out.println("0");
		int by1 = in.read();
		System.out.println("1");
		int by2 = in.read();
		System.out.println("2");
		int by3 = in.read();
		System.out.println("3");
		
		System.out.println(by1+" "+(char)by1);
		System.out.println('\r'+0);
		System.out.println('\n'+0);
		System.out.println(by2);
		System.out.println(by3);
		
	}
}
