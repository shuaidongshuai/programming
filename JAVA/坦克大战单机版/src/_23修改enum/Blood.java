package _23ÐÞ¸Äenum;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Rectangle;
import java.util.Random;

public class Blood {
	private int x ,y , w ,h;
	private TankClient tc;
	private boolean live = true;
	private Random rand = new Random();


	Blood(TankClient tc){
		this.tc = tc;
	}
	
	public boolean isLive() {
		return live;
	}
	public void setLive(boolean live) {
		this.live = live;
	}

	public void draw(Graphics g){
		if(!live) return ;
		x = rand.nextInt(tc.WIDTH/50)+600;
		y = rand.nextInt(tc.HEIGHT/50)+150;
		Color c = g.getColor();
		g.setColor(Color.green);
		g.fillRect(x, y, 20, 20);
		g.setColor(c);
	}
	
	public Rectangle getRect(){
		return new Rectangle(x, y, 20, 20);
	}
	
}
