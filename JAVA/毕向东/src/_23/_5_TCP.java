package _23;

import java.net.*;
import java.io.*;

public class _5_TCP {
	public static void main(String[] args) throws Exception {
		//创建客服端的socket服务，指定目的主机和端口
		Socket s = new Socket("192.168.1.1",10000);
		
		//为了发送数据，应该获取socket流中的输出流
		OutputStream out = s.getOutputStream();
		out.write("我是客户端".getBytes());
		
		//读服务端数据
		InputStream in = s.getInputStream();
		byte[] buf = new byte[1024];
		int len = in.read(buf);
		System.out.println(new String(buf,0,len));
		
		s.close();
	}
}
