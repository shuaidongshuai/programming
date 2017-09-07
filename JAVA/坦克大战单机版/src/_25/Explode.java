package _25;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Toolkit;
/**
 * 爆炸类
 * @author ☆东★
 *
 */
public class Explode {//爆炸
	private int x , y;
	private boolean live = true;
	private int step = 0;//画到第几步了
	private TankClient tc;
	private static boolean init;
	private static Toolkit tk = Toolkit.getDefaultToolkit();
	private static Image[] image = {
			tk.getImage(Explode.class.getClassLoader().getResource("images/0.gif")),
			tk.getImage(Explode.class.getClassLoader().getResource("images/1.gif")),
			tk.getImage(Explode.class.getClassLoader().getResource("images/2.gif")),
			tk.getImage(Explode.class.getClassLoader().getResource("images/3.gif")),
			tk.getImage(Explode.class.getClassLoader().getResource("images/4.gif")),
			tk.getImage(Explode.class.getClassLoader().getResource("images/5.gif")),
			tk.getImage(Explode.class.getClassLoader().getResource("images/6.gif")),
			tk.getImage(Explode.class.getClassLoader().getResource("images/7.gif")),
			tk.getImage(Explode.class.getClassLoader().getResource("images/8.gif")),
			tk.getImage(Explode.class.getClassLoader().getResource("images/9.gif")),
			tk.getImage(Explode.class.getClassLoader().getResource("images/10.gif"))
	};
	
	Explode(int x,int y,TankClient tc){
		this.x = x;
		this.y = y;
		this.tc = tc;
	}
	
	public void draw(Graphics g){
		if(!init){
			for (int i = 0; i< image.length; i++) {//会发现第一次打敌人，不会出现爆炸。可能是系统第一次 加载图片的时候不会放到内存中
				g.drawImage(image[i], 100, 100, null);
			}
			init = true;
		}
		
		if(!live){
			tc.explodes.remove(this);//当爆炸不存在了，就从TankClient的爆炸集合中移除当前爆炸
			return ;
		}
		if(step==11){
			this.live = false;
			this.step = 0;
			return ;
		}
		g.drawImage(image[step++], x, y, null);
	}
}
