package _4;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.*;
/*
 *  void setTitle(String title)    将此窗体的标题设置为指定的字符串。 
 */
public class ChatClient extends Frame{
	Socket s ;
	PrintWriter pw ;
	TextField tf = new TextField();
	TextArea ta = new TextArea();
	Dialog Dia = new Dialog(this,"记得常来玩啊",true);
	Button okButton = new Button("你要退/(ㄒoㄒ)/~~出啊                   点我点我");
	
	public void launchFrame(){
		setTitle("欢迎来到东东聊天室");
		setBounds(400,100,600,500);
		
		add(ta);					//让TextArea铺满
		add(tf,BorderLayout.SOUTH);//把TextField放到南边
		Dia.add(okButton);//可加可不加，为了美观
		Dia.setBounds(500,300,300,100);//对话框中的位置+大小
		
		pack();//自动调整合适的大小
		//窗口关闭时的动作
		this.addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent e) {
				disconnect();
				System.exit(0);
			}
		});
		//对话框关闭时的动作
		Dia.addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent e) {
				Dia.setVisible(false);
			}
		});
		
		tf.addActionListener(new TFListener());//向TextField中，加入TestField监听
		setVisible(true);
		
		connect();//连接服务器
		
		ta.append("东东客服：欢迎带到东东联盟，请在下面框框内咨询问题（以回车结束）\r\n东东客服：请问有什么可以帮你的么?\r\n");
		
		new Thread(new ServerReadr()).start();//开启读
	}
	
	//关于TextField的监听
	private class TFListener implements ActionListener{
		public void actionPerformed(ActionEvent e) {
			String str = tf.getText().trim();//获取TestField里面的内容
			ta.append("me我："+str+"\r\n");//在TextArea中打印		TestField里面的内容
			tf.setText("");//清空TestField
			try {
				pw.println(str);
			} catch (Exception e1) {
				e1.printStackTrace();
			}
		}
	}
	//连接主机时的操作
	public void connect(){
		try {
			s = new Socket("192.168.1.1",8888);
//			s= new Socket("chenmingdong666.6655.la",29597);
			pw = new PrintWriter(s.getOutputStream(),true);
		} catch (UnknownHostException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
	}
	//关闭时的操作
	public void disconnect(){
		try {
			Dia.setVisible(true);
			pw.println("我退出了");
			s.shutdownOutput();
			s.close();
		} catch (IOException e) {
			return ;
		}
		pw.close();
	}
	//读取服务器发过来的信息
	class ServerReadr implements Runnable{
		private BufferedReader bufr;
		private String str = null;
		public void run() {
			while(s!=null){
				try {
					bufr = new BufferedReader(new InputStreamReader(s.getInputStream()));
					if((str = bufr.readLine())== null){
						bufr.close();
						return ;
					}
					ta.append("东东客服："+str+"\r\n");
					} catch (IOException e) {
						return ;
					}
			}
		}
	}
	
	public static void main(String[] args) {
		new ChatClient().launchFrame();
	}
}
