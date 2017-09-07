package _5;

import java.awt.*;
import java.awt.event.*;

public class Tank {
	private int x,y;

	public Tank(int x, int y) {
		this.x = x;
		this.y = y;
	}
	
	public void drawTank(Graphics g){
		Color c = g.getColor();//获取此图形上下文的当前颜色。
		g.setColor(Color.blue);
		g.fillOval(x, y, 30, 30);
		
		g.setColor(c);//将此图形上下文的当前颜色设置为指定颜色
	}
	
	public static void main(String[] args) {
		
	}
	//添加按键事件
	class KeyPressed extends KeyAdapter{
		public void keyPressed(KeyEvent e) {
			int key = e.getKeyCode();
			switch(key){
			case KeyEvent.VK_UP    : y-=5;break;//注意这里不能用e.VK_UP  e是变量了，不能出现变量
			case KeyEvent.VK_DOWN  : y+=5;break;
			case KeyEvent.VK_RIGHT : x+=5;break;
			case KeyEvent.VK_LEFT  : x-=5;break;
			}
		}
	}
}
