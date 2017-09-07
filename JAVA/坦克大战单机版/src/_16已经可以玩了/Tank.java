package _16已经可以玩了;

import java.awt.*;
import java.awt.event.*;
import java.util.*;

public class Tank {
	private int x,y;// x  y  代表了tank现在的位置
	private static final int WIDTH = 30,HEIGHT = 30;//坦克大小
	private static final int XSPEED = 5,YSPEED = 5;//坦克xy方向运动速度	
	private int GAME_LEVEL = 12;//默认游戏难度为12  越高越简单，最高17  最低3
	//想让Tank向8个方向走
	private boolean bL = false ,bU = false ,bR = false ,bD = false;//用于记录  键盘按下的  上下左右  （按下之后就设置为True）
	enum Direction {L, LU, U, RD, R, RU, D, LD, STOP};//用来表示Tank是朝 哪个方法走的   以后这个枚举就来代表坦克的走向
	private Direction dir = Direction.STOP;//坦克的最开始的方向
	private Direction ptDir = Direction.D;//炮筒最开始的方向
	private TankClient tc = null;
	private boolean good ;
	private boolean live = true;
	private static Random rand = new Random();
	private int step = rand.nextInt(15)+3;//设置随机朝一个方向移动的步数，不然老是在同一个地方乱动
	
	public boolean isGood() {
		return good;
	}
	public boolean isLive() {
		return live;
	}

	public void setLive(boolean live) {
		this.live = live;
	}

	public Tank(int x,int y,boolean good,Direction dir,TankClient tc){//获取TankClient的引用，让Tank可以调用TankClient里面的数据，因为子弹的方向是由Tank决定的，而TankClient要获取Bullets方向
		this.x = x;
		this.y = y;
		this.good = good;
		this.dir = dir;
		this.tc = tc;
	}
	
	public void drawTank(Graphics g){//坦克自己画自己
		if(!live){
			tc.enemyTank.remove(this);
			return;
		}
		
		Color c = g.getColor();//获取此图形上下文的当前颜色。
		if(good)
			g.setColor(Color.cyan);
		else
			g.setColor(Color.blue);
		g.fillOval(x, y, WIDTH, HEIGHT);
		g.setColor(c);//将此图形上下文的当前颜色设置为指定颜色
		
		ptDraw(g);
		move();
	}
	//用于判断  tank 往哪个方向走		用枚举里面的数   来判断是往哪个方向走的	 从此 x y 的改变就从move这个方法里面改变（原来是从KeyAdapter 里面改变的）
	private void move(){
		switch(dir){//dir决定最终坦克的方向
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
		
		if(x<=5)
			x = 5;
		if(y<=30)
			y = 30;
		if(x>=TankClient.WIDTH-Tank.WIDTH-5)
			x = TankClient.WIDTH-Tank.WIDTH-5;
		if(y>=TankClient.HEIGHT-Tank.HEIGHT-5)
			y=TankClient.HEIGHT-Tank.HEIGHT-5;
		
		
		if(this.dir != Direction.STOP)//如果坦克方向不为Stop，，那么改变炮筒方向（与坦克方向一样）
			ptDir = dir;
		
		if(!good){//如果是敌方坦克
			if(step == 0){
				Direction[] arr = Direction.values();// 把enum转化为数组
				int r = rand.nextInt(arr.length);//从0到arr的最大长度
				dir = arr[r];
				step = rand.nextInt(15)+3;//生成0---14之间的数
				
				//给地方tank增加炮弹。。不能太密集
				if(step>=GAME_LEVEL) fire();
			}
			step--;
		}
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
	}
	
	private void fire(){//Tank发射子弹   给子弹一个信号，，让子弹往自己指定的方向发子弹
		if(good)
			tc.times++;//每次 发子弹的时候，设置一个计数器

		int x = this.x + Tank.WIDTH/2 - Bullets.WIDTH/2;
		int y = this.y + Tank.HEIGHT/2 - Bullets.HEIGHT/2;
		Bullets b = new Bullets(x,y,ptDir,good,tc);
		if(tc.times<20 && live) //如果发子弹次数少于20次，而且坦克活着，那么就装一发炮弹
			tc.myBullets.add(b);
	}
	
	public Rectangle getRect(){
		return new Rectangle(x,y,WIDTH,HEIGHT);
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
			
			case KeyEvent.VK_Q	   : fire(); break;//按下Q键就可以获取子弹  的位置和  坦克现在的方向（子弹的方向）然后调用paint函数重画子弹
			case KeyEvent.VK_SPACE : tc.times = 0;
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
