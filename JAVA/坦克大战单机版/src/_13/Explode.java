package _13;

import java.awt.*;

public class Explode {//爆炸
	int x , y;
	private boolean live = true;
	private int[] diameter = {5,10,20,25,30,35,40,35,30,28,26,13,7,1};//diameter直径
	private int step = 0;//画到第几步了
	private TankClient tc;
	
	Explode(int x,int y,TankClient tc){
		this.x = x;
		this.y = y;
		this.tc = tc;
	}
	
	public void draw(Graphics g){
		if(!live) return ;
		if(step==diameter.length){
			this.live = false;
			this.step = 0;
			return ;
		}
		
		Color c = g.getColor();
		g.setColor(Color.orange);
		g.fillOval(x++, y++, diameter[step], diameter[step++]);
		g.setColor(c);
	}
	
}
