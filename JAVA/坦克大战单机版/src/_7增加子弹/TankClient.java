
package _7增加子弹;

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
	private static final int WIDTH=800,HEIGHT=600;
	private Image offScreamImage = null;
	
	Tank myTank = new Tank(50,50);
	Bullets myBullets = new Bullets(50,50,Tank.Direction.D);
	
	public void paint(Graphics g) {
		myTank.drawTank(g);
		myBullets.drawBullets(g);
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

	
	public void lauchFrame(){
		this.setBounds(250,80,WIDTH,HEIGHT);
		this.setResizable(false);//设置不可以调整大小
		this.setBackground(Color.gray);
		
		this.addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}
		});
		this.addKeyListener(myTank.new MyKeyEvent());
		
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
					Thread.sleep(20);//每80毫秒重画一次
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}
	}
}
