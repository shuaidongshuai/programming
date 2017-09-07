package _17增加了墙;

import java.awt.*;

public class Explode {//爆炸
	private int x , y;
	private boolean live = true;
	private int[] diameter = {2,5,10,20,25,25,18,10,5,2};//diameter直径
	private int step = 0;//画到第几步了
	private TankClient tc;
	
	Explode(int x,int y,TankClient tc){
		this.x = x;
		this.y = y;
		this.tc = tc;
	}
	
	public void draw(Graphics g){
		if(!live){
//						 remove(Object o) 移除此列表中首次出现的指定元素（如果存在）。 
			tc.explodes.remove(this);//当爆炸不存在了，就从TankClient的爆炸集合中移除当前爆炸
			return ;
		}
		if(step==diameter.length){
			this.live = false;
//			this.step = 0;
			return ;
		}
		
		Color c = g.getColor();
		g.setColor(Color.orange);
		g.fillOval(x++, y, diameter[step], diameter[step++]);
		g.setColor(c);
	}
	
}
