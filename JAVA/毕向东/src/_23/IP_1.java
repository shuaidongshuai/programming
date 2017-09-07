package _23;

import java.net.InetAddress;
import java.net.UnknownHostException;

public class IP_1 {
	public static void main(String[] args) throws UnknownHostException {
		InetAddress i = InetAddress.getLocalHost();
		System.out.println(i.toString());
		System.out.println("name: "+i.getHostName());
		System.out.println("ip: "+i.getHostAddress());
		
		InetAddress ia = InetAddress.getByName("www.baidu.com");
		System.out.println("address : "+ia.getHostAddress());
		System.out.println("name : "+ia.getHostName());
		
	}
}
