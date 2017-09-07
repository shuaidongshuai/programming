
package _4;

import java.awt.*;
import java.awt.event.*;
/*
 *  void setResizable(boolean resizable) 
          设置此窗体是否可由用户调整大小。 
    
    public abstract Color getColor()获取此图形上下文的当前颜色。
    
    public abstract void setColor(Color c)将此图形上下文的当前颜色设置为指定颜色。使用此图形上下文的所有后续图形操作均使用这个指定的颜色。 
    
    public void repaint()重绘此组件。 
	如果此组件是轻量级组件，则此方法会尽快调用此组件的 paint 方法。否则此方法会尽快调用此组件的 update 方法。
	
	abstract  boolean drawImage(Image img, int x, int y, ImageObserver observer) 
          绘制指定图像中当前可用的图像。 

 */
public class TankClient extends Frame{
	private int x=50 , y=50;
	private static final int WIDTH=800,HEIGHT=600;
	private Image offScreamImage = null;
	
	public void paint(Graphics g) {
		Color c = g.getColor();//获取此图形上下文的当前颜色。
		g.setColor(Color.blue);
		g.fillOval(x, y, 30, 30);
		
		g.setColor(c);//将此图形上下文的当前颜色设置为指定颜色
	}

	//添加双缓冲消除闪烁现象
	public void update(Graphics g) {
		if(offScreamImage == null){
			offScreamImage = this.createImage(WIDTH,HEIGHT);//把所有东西都画在这张图片上
		}
			
		Graphics gOffScream = offScreamImage.getGraphics();//获取这张图片的画笔
		//下面是重画屏幕，使他恢复原来的颜色
		Color c = g.getColor();
		gOffScream.setColor(Color.gray);
		gOffScream.fillRect(0, 0, WIDTH, HEIGHT);
		gOffScream.setColor(c);
		
		paint(gOffScream);//调用paint方法。使这张图片也画上   paint方法里面的图片
		
		g.drawImage(offScreamImage, 0, 0, null);
	}
	
//	//用继承的方法  实现键盘监听器   相比于接口，，可以烧写两个方法
//	private class KeyMonitor extends KeyAdapter{//KeyAdapter implements KeyListener
//		public void keyPressed(KeyEvent e) {
//			System.out.println("dong");
//		}
//	}

	public void lauchFrame(){
		this.setBounds(250,80,WIDTH,HEIGHT);
		this.setResizable(false);//设置不可以调整大小
		this.setBackground(Color.gray);
		
		this.addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}
		});
		this.addKeyListener(new KeyAdapter() {
			public void keyPressed(KeyEvent e) {
				int key = e.getKeyCode();
				switch(key){
				case KeyEvent.VK_UP    : y-=5;break;//注意这里不能用e.VK_UP  e是变量了，不能出现变量
				case KeyEvent.VK_DOWN  : y+=5;break;
				case KeyEvent.VK_RIGHT : x+=5;break;
				case KeyEvent.VK_LEFT  : x-=5;break;
				}
			}
		});
		
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
//				try {
//					Thread.sleep(1000);//每80毫秒重画一次
//				} catch (InterruptedException e) {
//					e.printStackTrace();
//				}
			}
		}
	}
}
