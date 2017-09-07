package _18自己增加的功能_复活_闪现_增加敌人坦克;

import java.awt.Graphics;
import java.awt.Rectangle;

public class Wall {
	private int x,y,w,h;
	private TankClient tc;

	public Wall(int x, int y, int w, int h, TankClient tc) {
		super();
		this.x = x;
		this.y = y;
		this.w = w;
		this.h = h;
		this.tc = tc;
	}
	
	public void draw(Graphics g){
		g.fillRect(x, y, w, h);
	}
	
	public Rectangle getRect(){
		return new Rectangle(x,y,w,h);
	}
	
}
