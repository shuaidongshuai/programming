package _4;

import java.awt.BorderLayout;
import java.awt.Frame;
import java.awt.TextArea;
import java.awt.TextField;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class ChatServer2 {
	public static void main(String[] args) {
		Socket s = null;
		int count = 1;
		try {
//			ServerSocket ss = new ServerSocket(8888);//创建服务器10001
			ServerSocket ss = new ServerSocket(8888);//创建服务器
			
			
			while(true){
				s = ss.accept();//接收客户端请求
				new ServerFrame(s,count++).launchFrame();//每接收一个客户端就创建一个线程
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
//使服务端有可视窗口
class ServerFrame extends Frame{
	Socket s = null;
	PrintWriter pw ;
	BufferedReader bufr;
	String str = null;
	int count = 0 ;
	TextField tf = new TextField();
	TextArea ta = new TextArea();
	
	ServerFrame(Socket s,int count){
		this.s = s;
		this.count = count;
	}
	//主要就是调用这个函数
	public void launchFrame(){
		setTitle("欢迎来到东东聊天室");
		setBounds(400,100,700,600);
		
		add(ta);
		add(tf,BorderLayout.SOUTH);
		pack();
		this.addWindowListener(new WindowAdapter(){//关闭窗口时
			public void windowClosing(WindowEvent e) {
				disconnect();
			}
		});
		tf.addActionListener(new TFListener());//加入TestField监听
		setVisible(true);
		
		new Thread(new ClientReader()).start();//为读取客户端专门创建一个线程
	}
	//关于TextField的监听
	private class TFListener implements ActionListener{
		public void actionPerformed(ActionEvent e) {
			String str = tf.getText().trim();//获取TestField里面的内容
			ta.append("服务器："+str+"\r\n");//在TextArea中打印		TestField里面的内容
			tf.setText("");//清空TestField
			try {
				pw = new PrintWriter(s.getOutputStream(),true);
				pw.println(str);
			} catch (Exception e1) {
				e1.printStackTrace();
			}
		}
	}
	private void disconnect(){
		try {
			setVisible(false);
			if(s!=null)
			s.close();
		} catch (IOException e) {
			return ;
		}
		pw.close();
	}
	
	class ClientReader implements Runnable{
		private String str = null;
		public void run() {
			ta.append("Client："+count+"  来了\r\n");
			while(s!=null){
				try {
					bufr = new BufferedReader(new InputStreamReader(s.getInputStream()));
					if((str = bufr.readLine())== null){
						bufr.close();
						return ;
					}
					ta.append("Client："+str+"\r\n");
					} catch (IOException e) {
//						System.out.println("客户端退出");
						return ;
					}
			}
		}
	}
}
