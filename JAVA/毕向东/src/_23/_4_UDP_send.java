package _23;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class _4_UDP_send {
	public static void main(String[] args) throws IOException {
		DatagramSocket ds = new DatagramSocket();
		BufferedReader bufr = new BufferedReader(new InputStreamReader(System.in));
		
		String line = null;
		while((line = bufr.readLine())!=null){
			if("886".equals(line))
				break;
			byte[] buf = line.getBytes();
			DatagramPacket dp = new DatagramPacket(buf,buf.length,InetAddress.getByName("192.168.1.1"),10001);//封装成包
			
			ds.send(dp);//把包发出去
		}
		bufr.close();
		ds.close();
	}
}
