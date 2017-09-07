package _15;

import java.awt.*;
import java.util.List;

public class Bullets {//子弹类
	private int x,y;//坦克的位置，也是子弹的位置
	private boolean live = true;
	public static final int WIDTH = 10, HEIGHT = 10;//子弹大小
	private static final int XSPEED = 10,YSPEED = 10;//子弹速度
	private TankClient tc;
	Tank.Direction dir;
	
	public Bullets(int x, int y, Tank.Direction dir) {
		this.x = x;
		this.y = y;
		this.dir = dir;
	}
	public Bullets(int x,int y,Tank.Direction dir,TankClient tc){
		this(x, y, dir);
		this.tc = tc;
	}
	
	public void drawBullets(Graphics g){
		if(!live) return;
		Color c = g.getColor();
		g.setColor(Color.black);
		g.fillOval(	x, y, WIDTH, HEIGHT);
		g.setColor(c);
		
		move();
	}
	
	//子弹自己的移动方向速度
	private void move() {
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
		}
//		if(x<0 || y<0 || x>TankClient.WIDTH || y>TankClient.HEIGHT){
//			live = false;
//		}
	}
	
	public Rectangle getRect(){
		return new Rectangle(x,y,WIDTH,HEIGHT);
	}
	
	
	//下面就是判断  坦克是否被击中，一级击中后会发生的事，一个函数可以解决，第一个函数里面就是循环，可以把它放在第二个函数里（只是不容易看而已）
	public void hitTanks(List<Tank> tanks){
		for(int i=0;i<tanks.size();i++)
			hitTank(tanks.get(i));//每次，挨个挨个的判断每一辆坦克是否被击中
	}
	public boolean hitTank(Tank t){					//坦克必须活着，不然死了以后，子弹打到相同位置，子弹也会消失
		if(this.getRect().intersects(t.getRect()) && t.isLive()){//boolean intersects(Rectangle r) 确定此 Rectangle 是否与指定的 Rectangle 相交。 
			t.setLive(false);//把塔克也弄死，，，把标志live设置为false（死）
			this.live = false;//把子弹也弄消失
			Explode e = new Explode(x,y,tc);//每次击中再增加一个爆炸类
			tc.explodes.add(e);//给TankClient的爆炸集合，增加一个爆炸
			return true;
		}
		return false;
	}
	
}
