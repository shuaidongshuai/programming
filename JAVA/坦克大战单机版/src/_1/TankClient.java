package _1;

import java.awt.*;
import java.awt.event.*;
/*
 *  void setResizable(boolean resizable) 
          设置此窗体是否可由用户调整大小。 
 */
public class TankClient extends Frame{
	
	public void lauchFrame(){
		this.setBounds(250,100,800,600);
		
		this.addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}
		});
		this.setResizable(false);
		setVisible(true);
	}
	
	public static void main(String[] args) {
		new TankClient().lauchFrame();
	}
}
