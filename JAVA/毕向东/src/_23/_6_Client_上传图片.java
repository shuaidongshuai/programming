package _23;

import java.io.FileInputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
/*
 * 这是程序完全自己写的没有抄视频
 * 实现上传图片功能
 * 不过也有好多没弄明白
 * 那些没有明白的东西都跳过了，用来一个特别笨的方法才做出来
 * 
 * 1，获取文件名长度，把这个整数又转化为了字符串(占一个字节)，然后又转为字节数组发出去(发出去一个字节)
 */
public class _6_Client_上传图片 {
	public static void main(String[] args) throws Exception {
		Socket s = new Socket("192.168.1.1",10006);
		
		String name = "4.jpg";
		FileInputStream fis = new FileInputStream("C:\\Users\\37916\\Pictures\\Camera Roll\\"+name);
		OutputStream os = s.getOutputStream();
		
		byte[] buf = new byte[1024];
		int len = 0;
		
//		String l = name.length() + "";//字符串		一个字符1字节  汉字两个字节
//		os.write(l.getBytes());//发出一个字节
		//或者
		buf[0] = (byte)name.length();//把整型强制类型转换就可以了
		os.write(buf,0,1);
		
		buf = name.getBytes();
		os.write(buf);
		
		while((len = fis.read(buf))!=-1){
			os.write(buf,0,len);
		}
		
		s.shutdownOutput();//关闭客户端输出流，相当于给流中加入一个结束标记-1, 这样服务端就可以跳出while循环
		
		InputStream is = s.getInputStream();
		byte[] buf1 = new byte[1024];
		int l = is.read(buf1);
		System.out.println(new String(buf1,0,l));
		
		is.close();
		os.close();
		fis.close();
	}
}
