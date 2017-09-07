package _21;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.Arrays;

/*
 * 编码：字符串变成字节数组
 * 
 * 解码：字节数组变成字符串
 * 
 */
public class IO_5_字节编码 {
	public static void main1(String[] args) throws Exception {
		String s = "你好";
		
		byte[] b1 = s.getBytes("GBK");//编码
		byte[] b2 = s.getBytes("UTF-8");//编码
		System.out.println(Arrays.toString(b1));//4个字节
		System.out.println(Arrays.toString(b2));//6个字节
		
		String s1 = new String(b1,"GBK");//正确解码
		System.out.println(s1);
		
		s1 = new String(b1,"UTF-8");//错误解码
		System.out.println(s1);
		
		s1 = new String(b2,"GBK");//错误解码
		System.out.println(s1);
	}
	public static void main(String[] args) throws IOException {
		String s = "你好";
			
		byte[] b1 = s.getBytes("GBK");//编码

		//下面是演示，当错误解码之后，还能否通过再次编码，进行正确编码
		System.out.println("正确解码字节个数："+Arrays.toString(b1));
		
		String s2 = new String(b1,"iso8859-1");//错误解码
		System.out.println("so8859-1解码："+s2);
		
//		byte[] b3 = s2.getBytes("iso8859-1");//再次编码（部分于欧洲使用的语言）
//		System.out.println("错误编码字节个数"+Arrays.toString(b3));
		byte[] b3 = s.getBytes("UTF-8");//错误解码
		System.out.println("错误解码字节个数："+Arrays.toString(b3));
		String s3 = new String(b3,"gbk");//尽管用来gbk  但是由于开始解码错误，所以导致最后解码错误，，但是如果开始用iso8859-1解码就不会出问题
		System.out.println("解码："+s3);													//原因在于UTF-8和gbk都识别中文，iso8859-1不识别中文
	}
}
