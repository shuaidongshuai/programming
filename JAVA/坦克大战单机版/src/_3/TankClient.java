package _3;

import java.awt.*;
import java.awt.event.*;
/*
 *  void setResizable(boolean resizable) 
          设置此窗体是否可由用户调整大小。 
    
    public abstract Color getColor()获取此图形上下文的当前颜色。
    
    public abstract void setColor(Color c)将此图形上下文的当前颜色设置为指定颜色。使用此图形上下文的所有后续图形操作均使用这个指定的颜色。 
    
    public void repaint()重绘此组件。 
	如果此组件是轻量级组件，则此方法会尽快调用此组件的 paint 方法。否则此方法会尽快调用此组件的 update 方法。

 */
public class TankClient extends Frame{
	private int x=50 , y=50;
	
	public void paint(Graphics g) {
		Color c = g.getColor();//获取此图形上下文的当前颜色。
		g.setColor(Color.blue);
		g.fillOval(x, y, 30, 30);
		
		g.setColor(c);//将此图形上下文的当前颜色设置为指定颜色
		
		y+=5;
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
		
		new Thread(new PaintThread()).start();//创建一个线程，重画
	}
	
	public static void main(String[] args) {
		new TankClient().lauchFrame();
	}
	
	//内部类
	private class PaintThread implements Runnable{
		public void run() {
			while(true){
				repaint();
				try {
					Thread.sleep(80);//每80毫秒重画一次
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}
	}
}
