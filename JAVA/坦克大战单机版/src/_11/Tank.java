package _11;

import java.awt.*;
import java.awt.event.*;

public class Tank {
	private int x,y;// x  y  代表了tank现在的位置
	private static final int WIDTH = 30,HEIGHT = 30;//坦克大小
	private static final int XSPEED = 5,YSPEED = 5;//坦克xy方向运动速度	
	//想让Tank向8个方向走
	private boolean bL = false ,bU = false ,bR = false ,bD = false;//用于记录  键盘按下的  上下左右  （按下之后就设置为True）
	enum Direction {L, LU, U, RD, R, RU, D, LD, STOP};//用来表示Tank是朝 哪个方法走的   以后这个枚举就来代表坦克的走向
	private Direction dir = Direction.STOP;//坦克的最开始的方向
	private Direction ptDir = Direction.D;//炮筒最开始的方向
	private TankClient tc = null;
	
	public Tank(int x,int y,TankClient tc){//获取TankClient的引用，让Tank可以调用TankClient里面的数据，因为子弹的方向是由Tank决定的，而TankClient要获取Bullets方向
		this.x = x;
		this.y = y;
		this.tc = tc;
	}
	
	public void drawTank(Graphics g){
		Color c = g.getColor();//获取此图形上下文的当前颜色。
		g.setColor(Color.blue);
		g.fillOval(x, y, WIDTH, HEIGHT);
		g.setColor(c);//将此图形上下文的当前颜色设置为指定颜色
		
		ptDraw(g);
		move();
	}
	//用于判断  tank 往哪个方向走		用枚举里面的数   来判断是往哪个方向走的	 从此 x y 的改变就从move这个方法里面改变（原来是从KeyAdapter 里面改变的）
	private void move(){
//		int xBorder = x,yBorder = y;
		switch(dir){
		case L : 
			x-=XSPEED; break;
		case LU :
			x-=XSPEED; y-=YSPEED; break;
		case U :
			y-=XSPEED; break;
		case RD :
			x+=XSPEED; y+=YSPEED; break;
		case R :
			x+=XSPEED; break;
		case RU :
			x+=XSPEED; y-=YSPEED; break;
		case D :
			y+=YSPEED; break;
		case LD :
			x-=XSPEED; y+=YSPEED; break;
		case STOP : break;
		}
//		if(x<=0 || y<=0 || x>=TankClient.WIDTH-Tank.WIDTH || y>=TankClient.HEIGHT-Tank.WIDTH){
//			x = xBorder;
//			y = yBorder;
//		}
		if(x<=0)
			x = 0;
		if(y<=30)
			y = 30;
		if(x>=TankClient.WIDTH-Tank.WIDTH)
			x = TankClient.WIDTH-Tank.WIDTH;
		if(y>=TankClient.HEIGHT-Tank.WIDTH)
			y=TankClient.HEIGHT-Tank.WIDTH;
	}
	//画出炮筒
	private void ptDraw(Graphics g){
		switch(ptDir){
		case L : 
			g.drawLine(x+Tank.WIDTH/2, y+Tank.HEIGHT/2, x, y+Tank.HEIGHT/2); break;
		case LU :
			g.drawLine(x+Tank.WIDTH/2, y+Tank.HEIGHT/2, x, y); break;
		case U :
			g.drawLine(x+Tank.WIDTH/2, y+Tank.HEIGHT/2, x+Tank.HEIGHT/2, y); break;
		case RD :
			g.drawLine(x+Tank.WIDTH/2, y+Tank.HEIGHT/2, x+Tank.HEIGHT, y+Tank.HEIGHT); break;
		case R :
			g.drawLine(x+Tank.WIDTH/2, y+Tank.HEIGHT/2, x+Tank.HEIGHT, y+Tank.HEIGHT/2); break;
		case RU :
			g.drawLine(x+Tank.WIDTH/2, y+Tank.HEIGHT/2, x+Tank.HEIGHT, y); break;
		case D :
			g.drawLine(x+Tank.WIDTH/2, y+Tank.HEIGHT/2, x+Tank.HEIGHT/2, y+Tank.HEIGHT); break;
		case LD :
			g.drawLine(x+Tank.WIDTH/2, y+Tank.HEIGHT/2, x, y+Tank.HEIGHT); break;
		}
	}
	
	private void realDirection(){//Tank真正走的方向  L, LU, U, RD, R, RU, D, LD, STOP   取决于dir的值
		if(bL && !bU && !bR && !bD)
			dir = Direction.L;
		else if(bL && bU && !bR && !bD)
			dir = Direction.LU;
		else if(!bL && bU && !bR && !bD)
			dir = Direction.U;
		else if(!bL && !bU && bR && bD)
			dir = Direction.RD;
		else if(!bL && !bU && bR && !bD)
			dir = Direction.R;
		else if(!bL && bU && bR && !bD)
			dir = Direction.RU;
		else if(!bL && !bU && !bR && bD)
			dir = Direction.D;
		else if(bL && !bU && !bR && bD)
			dir = Direction.LD;
		else if(!bL && !bU && !bR && !bD)
			dir = Direction.STOP;
		
		if(dir != Direction.STOP)
			ptDir = dir;
	}
	
	private Bullets fire(){//Tank发射子弹   给子弹一个信号，，让子弹往自己指定的方向发子弹
		int x = this.x + Tank.WIDTH/2 - Bullets.WIDTH/2;
		int y = this.y + Tank.HEIGHT/2 - Bullets.HEIGHT/2;
		Bullets b = new Bullets(x,y,ptDir);
		return b;
	}
	
	//添加按键事件
	class MyKeyEvent extends KeyAdapter{
		public void keyPressed(KeyEvent e) {
			int key = e.getKeyCode();
			switch(key){
			case KeyEvent.VK_UP    : bU = true; break;//注意这里不能用e.VK_UP  e是变量了，不能出现变量
			case KeyEvent.VK_DOWN  : bD = true; break;
			case KeyEvent.VK_RIGHT : bR = true; break;
			case KeyEvent.VK_LEFT  : bL = true; break;
			
			case KeyEvent.VK_Q	   : tc.myBullets.add(fire()); break;//按下Q键就可以获取子弹  的位置和  坦克现在的方向（子弹的方向）然后调用paint函数重画子弹
			case KeyEvent.VK_SPACE : tc.myBullets.clear();
			}
			realDirection();//上面只是判断是那几个按键被按下，，最终tank的走向是看dir的值
		}
		public void keyReleased(KeyEvent e) {
			int key = e.getKeyCode();
			switch(key){
			case KeyEvent.VK_UP    : bU = false; break;//注意这里不能用e.VK_UP  e是变量了，不能出现变量
			case KeyEvent.VK_DOWN  : bD = false; break;
			case KeyEvent.VK_RIGHT : bR = false; break;
			case KeyEvent.VK_LEFT  : bL = false; break;
			}
			realDirection();//上面只是判断是那几个按键被释放
		}
	}
}
