package _2;

import java.awt.*;
import java.awt.event.*;
/*
 *  void setResizable(boolean resizable) 
          设置此窗体是否可由用户调整大小。 
    
    public abstract Color getColor()获取此图形上下文的当前颜色。
    
    public abstract void setColor(Color c)将此图形上下文的当前颜色设置为指定颜色。使用此图形上下文的所有后续图形操作均使用这个指定的颜色。 
 */
public class TankClient extends Frame{
	public void paint(Graphics g) {
		Color c = g.getColor();//获取此图形上下文的当前颜色。
		g.setColor(Color.blue);
		g.fillOval(50, 50, 30, 30);
		
		g.setColor(c);//将此图形上下文的当前颜色设置为指定颜色
	}

	public void lauchFrame(){
		this.setBounds(250,100,800,600);
		
		this.addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}
		});
		this.setResizable(false);//设置不可以调整大小
		this.setBackground(Color.black);
		
		
		setVisible(true);
	}
	
	public static void main(String[] args) {
		new TankClient().lauchFrame();
	}
}
