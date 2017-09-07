package _6让Tank向8个方向走;

import java.awt.*;
import java.awt.event.*;

public class Tank {
	private int x,y;
	private static final int XSPEED = 5,YSPEED = 5;//坦克xy方向运动速度	
	//想让Tank向8个方向走
	private boolean bL = false ,bU = false ,bR = false ,bD = false;//用于记录  键盘按下的  上下左右  （按下之后就设置为True）
	enum Direction {L, LU, U, RD, R, RU, D, LD, STOP};//用来表示Tank是朝 哪个方法走的   以后这个枚举就来代表坦克的走向
	private Direction dir = Direction.STOP;//最开始设置为停止状态

	public Tank(int x, int y) {
		this.x = x;
		this.y = y;
	}
	
	public void drawTank(Graphics g){
		Color c = g.getColor();//获取此图形上下文的当前颜色。
		g.setColor(Color.blue);
		g.fillOval(x, y, 30, 30);
		
		g.setColor(c);//将此图形上下文的当前颜色设置为指定颜色
		
		move();
	}
	//用于判断  tank 往哪个方向走		用枚举里面的数   来判断是往哪个方向走的	 从此 x y 的改变就从move这个方法里面改变（原来是从KeyAdapter 里面改变的）
	private void move(){
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
	}
	
	private void realDirection(){//Tank真正走的方向  L, LU, U, RD, R, RU, D, LD, STOP
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
	//添加按键事件
	class MyKeyEvent extends KeyAdapter{
		public void keyPressed(KeyEvent e) {
			int key = e.getKeyCode();
			switch(key){
			case KeyEvent.VK_UP    : bU = true; break;//注意这里不能用e.VK_UP  e是变量了，不能出现变量
			case KeyEvent.VK_DOWN  : bD = true; break;
			case KeyEvent.VK_RIGHT : bR = true; break;
			case KeyEvent.VK_LEFT  : bL = true; break;
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
