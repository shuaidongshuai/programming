package _3;

import java.awt.*;
import java.awt.event.*;
import java.io.IOException;
import java.net.*;
public class ChatClient extends Frame{
	TextField tf = new TextField();
	TextArea ta = new TextArea();
	
	public void launchFrame(){
		setBounds(400,100,600,500);
		
		add(tf,BorderLayout.SOUTH);
		add(ta,BorderLayout.NORTH);
		pack();
		this.addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}
		});
		tf.addActionListener(new TFListener());//º”»ÎTestFieldº‡Ã˝
		setVisible(true);
		
		connect();
	}
	
	private class TFListener implements ActionListener{
		public void actionPerformed(ActionEvent e) {
			String s = tf.getText().trim();
			ta.setText(s);
			tf.setText("");
		}
		
	}
	
	public void connect(){
		try {
			Socket s = new Socket("192.168.1.1",10000);
System.out.println("connected");
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
	public static void main(String[] args) {
		new ChatClient().launchFrame();
	}
}
