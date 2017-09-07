package _23;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;

/*
 * 思路
 * 1，定义udpsocket服务,通常会监听一个指定端口
 * 2，定义一个数据包，用来储存接收到的数据，因为数据包对象中有更多功能可以提取字节数据中的不同数据信息
 * 3，通过socket服务的receive方法将收到的数据存入已定义好的数据包中
 * 4，通过数据包对象的特有功能，将这些不同的数据取出
 * 5，关闭资源
 */
public class _3_UDP {
	public static void main(String[] args) throws Exception {
		//1，创建UDP socket，建立端点
		DatagramSocket ds = new DatagramSocket(10001);//给客服端指定端口
		while(true){
			//2，定义数据包，用于储存数据
			byte[] buf = new byte[1024];
			DatagramPacket dp = new DatagramPacket(buf,buf.length);
			//3，通过服务的receive方法将受到的数据存入数据包中
			ds.receive(dp);
			//4,通过数据包的方法获取其中的数据
			String ip = dp.getAddress().getHostAddress();
			
			String data = new String(dp.getData(),0,dp.getLength());
			
			int port = dp.getPort();
			
			System.out.println("ip："+ip);
			System.out.println("data："+data);
			System.out.println("port："+port);
		}
	}
}
