package _23;

import java.io.BufferedReader;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

class Server implements Runnable{
	private Socket s;
	Server(Socket s){
		this.s = s;
	}
	public void run(){
		try {
			
			System.out.println("IP:"+s.getInetAddress().getHostAddress());//打印客户端IP
			
			InputStream is = s.getInputStream();//建立读取流
			
			byte[] buf = new byte[1024];
			int len = 0;
			
			is.read(buf,0,1);//把发过来的两个字节当一个字节存起来
//			len = buf[0] - '0';//发过来的是一个字符，也不算是
			len = (int )buf[0];//
			is.read(buf,0,len);
			String name = new String(buf,0,len);
			FileOutputStream fis = new FileOutputStream("E:\\programming\\JAVA\\垃圾文件\\"+name);//把将要发送过来的图片设置一个保存的位置
			
			while((len = is.read(buf))!=-1){//这里的is就是InputStream		对应客服端的OutputStream
				fis.write(buf,0,len);
			}
			
			OutputStream os = s.getOutputStream();
			os.write("上传成功".getBytes());
			
			os.close();
			fis.close();
			is.close();
		} catch (Exception e) {
			throw new RuntimeException("上传失败");
		}
	}
	
}
public class _6_Server_上传图片 {
	public static void main(String[] args) throws Exception {
		ServerSocket ss = new ServerSocket(10006);//这个要抛IOException		//创建端口为10000服务端
		
		while(true){
			Socket s = ss.accept();//接收客户端
			new Thread(new Server(s)).start();
		}
	}
}
