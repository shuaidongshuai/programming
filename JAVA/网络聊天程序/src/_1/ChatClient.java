package _1;

import java.awt.BorderLayout;
import java.awt.Frame;
import java.awt.TextArea;
import java.awt.TextField;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

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
		setVisible(true);
	}
	
	public static void main(String[] args) {
		new ChatClient().launchFrame();
	}
	
	
	
}
