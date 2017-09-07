package _25;

import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;

public class _4URL {
	public static void main(String[] args) throws IOException {
//		URL url = new URL("http://111.20.69.105:9998/?wlanuserip=10.70.182.158&wlanacname=0027.0029.290.00&ssid=CMCC-xacj");
		URL url = new URL("http://my.csdn.net/?ref=toolbar");
		
		System.out.println(url.getProtocol());
		System.out.println(url.getHost());
		System.out.println("port :"+url.getPort());
		System.out.println("path :"+url.getPath());
		System.out.println("file :"+url.getFile());
		System.out.println(url.getQuery());
	}
}
/*
String getFile() 
	获取此 URL 的文件名。 
String getHost() 
	获取此 URL 的主机名（如果适用）。 
String getPath() 
	获取此 URL 的路径部分。 
int getPort() 
	获取此 URL 的端口号。 
String getProtocol() 
	获取此 URL 的协议名称。 
String getQuery() 
	获取此 URL 的查询部分。 
*/