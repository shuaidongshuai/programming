package _23;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.UnknownHostException;

/*
 * 需求：通过udp传输方式，将一段文字数据发送出去
 * 
 * 1，建立updsocket
 * 2，提供数据，并将数据封装到数据包中
 * 3，通过socket服务的发送功能，将数据包发送出去
 * 4，关闭资源
 */
public class _2_UDP {
	public static void main(String[] args) throws Exception {
		//1，创建udp服务
		DatagramSocket ds = new DatagramSocket(8888);//给服务端指定端口
		
		//2，确定数据，并封装成数据包
		byte[] buf = "hello udp dong".getBytes();
		DatagramPacket dp = new DatagramPacket(buf,buf.length,InetAddress.getByName("192.168.1.1"),10000);
		
		ds.send(dp);//发送
		ds.close();
	}
}
