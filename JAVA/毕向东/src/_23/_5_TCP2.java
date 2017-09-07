package _23;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class _5_TCP2 {
	public static void main(String[] args) throws IOException, InterruptedException {
		//建立服务器socket服务，并监听一个端口
		ServerSocket ss = new ServerSocket(10000);
		
		while(true){
		Socket s = ss.accept();
		
		//获取客服端发过来的数据，那么要使用客户端对象的读取流来读取数据
		InputStream in = s.getInputStream();
		
		byte[] buf = new byte[1024];
		int len = in.read(buf);
		System.out.println(s.getInetAddress().getHostAddress());//public InetAddress getInetAddress()返回套接字连接的地址。
																//返回值是一个对象（通过方法来返回对象）再通过对象获取地址
																//String getHostName() 获取此 IP 地址的主机名 
		System.out.println(new String(buf,0,len));
		
		//给客户端发送数据
		OutputStream out = s.getOutputStream();
		Thread.sleep(4000);//服务端暂停4秒再给客户端发送数据
		out.write("服务端收到了".getBytes());
		
		s.close();//关闭客户端
		}
	}
}
