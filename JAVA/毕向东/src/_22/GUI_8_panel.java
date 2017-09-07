package _22;

import java.awt.Color;
import java.awt.Frame;
import java.awt.Panel;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class GUI_8_panel {
	public static void main(String[] args) {
		new MyFrame2("hello_dong",200,222,300,400);
	}
}
class MyFrame2 extends Frame{
	private Panel p1,p2,p3,p4;
	public MyFrame2(String s,int x,int y,int w,int h){
		super(s);
		setLayout(null);
		p1 = new Panel(null);
		p2 = new Panel(null);
		p3 = new Panel(null);
		p4 = new Panel(null);
		
		p1.setBounds(0,0,w/2,h/2);
		p2.setBounds(w/2,0,w/2,h/2);
		p3.setBounds(0,h/2,w/2,h/2);
		p4.setBounds(w/2,h/2,w/2,h/2);
		
		p1.setBackground(Color.blue);
		p2.setBackground(Color.black);
		p3.setBackground(Color.green);
		p4.setBackground(Color.red);
		
		add(p1);
		add(p2);
		add(p3);
		add(p4);
		
		setBounds(x,y,w,h);
		
		addWindowListener(new WindowAdapter(){

			@Override
			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}
		});
		
		setVisible(true);
	}
}
