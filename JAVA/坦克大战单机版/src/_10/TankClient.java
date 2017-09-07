
package _10;

import java.awt.*;
import java.awt.event.*;
import java.util.List;
import java.util.ArrayList;
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
	private Image offScreamImage = null;
	private Tank myTank = new Tank(50,50,this);//把TankClient对象传进去，使Tank可以操作TankClient里面的部分数据
	public static final int WIDTH=800,HEIGHT=600;
	public List<Bullets> myBullets = new ArrayList<Bullets>();//代表还有几发炮弹
	
	public void paint(Graphics g) {
		myTank.drawTank(g);
		
		g.setFont(new Font("", Font.PLAIN, 20));//设置字体
		if(myBullets.size()>=20){
			g.drawString("还有多少发炮弹:"+0, 10, 50);
			g.setColor(Color.red);
			g.setFont(new Font("", Font.BOLD, 20));
			g.drawString("没炮弹了", 20, 80);
		}
		else
		g.drawString("还有多少发炮弹:"+(20-myBullets.size()), 10, 50);
		
		if(myBullets.size()!=0 && myBullets.size()<=20)
		for(int i=0;i<myBullets.size();i++){
			Bullets b = myBullets.get(i);//创建这一发炮弹，然后画出来，就不管他了。
			b.drawBullets(g);
		}
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
