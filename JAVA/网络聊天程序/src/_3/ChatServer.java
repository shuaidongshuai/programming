package _3;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class ChatServer {
	public static void main(String[] args) {
		try {
			ServerSocket ss = new ServerSocket(10000);
			while(true){
				Socket s = ss.accept();
System.out.println(s.getLocalAddress().getHostAddress()+"------connected");
				
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		
		
	}
}
