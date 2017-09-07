package _24图片版.copy;

import java.awt.*;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Bullets {//子弹类
	private int x,y;//坦克的位置，也是子弹的位置
	private boolean live = true;
	public static final int WIDTH = 10, HEIGHT = 10;//子弹大小
	private static final int XSPEED = 10,YSPEED = 10;//子弹速度
	private TankClient tc;
	private boolean good;//用于标识子弹是哪一方的子弹
	Direction dir;
	
	private static Toolkit tk = Toolkit.getDefaultToolkit();
	private static Map<String,Image> imags = new HashMap<String,Image>();
	private static Image[] tankImage = null;
	static {
		tankImage = new Image[]{//L, LU, U, RD, R, RU, D, LD, STOP
				tk.getImage(Explode.class.getClassLoader().getResource("images/missileL.gif")),
				tk.getImage(Explode.class.getClassLoader().getResource("images/missileLU.gif")),
				tk.getImage(Explode.class.getClassLoader().getResource("images/missileU.gif")),
				tk.getImage(Explode.class.getClassLoader().getResource("images/missileRD.gif")),
				tk.getImage(Explode.class.getClassLoader().getResource("images/missileR.gif")),
				tk.getImage(Explode.class.getClassLoader().getResource("images/missileRU.gif")),
				tk.getImage(Explode.class.getClassLoader().getResource("images/missileD.gif")),
				tk.getImage(Explode.class.getClassLoader().getResource("images/missileLD.gif"))
		};
		imags.put("L", tankImage[0]);
		imags.put("LU", tankImage[1]);
		imags.put("U", tankImage[2]);
		imags.put("RD", tankImage[3]);
		imags.put("R", tankImage[4]);
		imags.put("RU", tankImage[5]);
		imags.put("D", tankImage[6]);
		imags.put("LD", tankImage[7]);
	}

	public Bullets(int x,int y,Direction dir,boolean good,TankClient tc){
		this.x = x;
		this.y = y;
		this.dir = dir;
		this.good = good;
		this.tc = tc;
	}
	
	public void draw(Graphics g){
		if(!live){
			tc.myBullets.remove(this);//用于删除子弹。不然这一发子弹打中敌人，另一个敌人来到这个地方也会死
			return;
		}
		if(good){
			Color c = g.getColor();
			g.setColor(Color.black);
			g.fillOval(	x, y, WIDTH, HEIGHT);
			g.setColor(c);
		}
		
			switch(dir){
			case L : 
				g.drawImage(imags.get("L"),x, y, null); break;
			case LU :
				g.drawImage(imags.get("LU"),x, y, null); break;
			case U :
				g.drawImage(imags.get("U"),x, y, null); break;
			case RD :
				g.drawImage(imags.get("RD"),x, y, null); break;
			case R :
				g.drawImage(imags.get("R"),x, y, null); break;
			case RU :
				g.drawImage(imags.get("RU"),x, y, null); break;
			case D :
				g.drawImage(imags.get("D"),x, y, null); break;
			case LD :
				g.drawImage(imags.get("LD"),x, y, null); break;
			case STOP :
				g.drawImage(imags.get("STOP"),x, y, null); break;
			}
		
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
		
		if(x<0 || y<0 || x>TankClient.WIDTH || y>TankClient.HEIGHT){//子弹超出边界  就让他在子弹集合中删除
			live = false;
		}
	}
	
	public Rectangle getRect(){
		return new Rectangle(x,y,WIDTH,HEIGHT);
	}
	
	
	//下面就是判断  坦克是否被击中，一级击中后会发生的事，一个函数可以解决，第一个函数里面就是循环，可以把它放在第二个函数里（只是不容易看而已）
	public void hitTanks(List<Tank> tanks){
		for(int i=0;i<tanks.size();i++)
			hitTank(tanks.get(i));//每次，挨个挨个的判断每一辆坦克是否被击中
	}
	public void hitTank(Tank t){
		//判断是否这辆坦克的面积，是否和子弹相碰，，，，坦克必须活着，不然死了以后，子弹打到相同位置，子弹也会消失
		if(this.getRect().intersects(t.getRect()) && t.isLive() && this.good != t.isGood()){//boolean intersects(Rectangle r) 确定此 Rectangle 是否与指定的 Rectangle 相交。 
			if(t.isGood()){
				t.setLife(t.getLife()-20);//每当我们被击中就减少20滴血
				if(t.getLife()<=0)
					t.setLive(false);
			} else//如果是敌方坦克就直接死
			t.setLive(false);//把塔克也弄死，，，把标志live设置为false（死）
			
			this.live = false;//把子弹也弄消失
			Explode e = new Explode(x,y,tc);//每次击中再增加一个爆炸类
			tc.explodes.add(e);//给TankClient的爆炸集合，增加一个爆炸
		}
	}
	
	public void hitWall(Wall w){//判断是否撞到墙了
		if(this.live && this.getRect().intersects(w.getRect())){
			this.live = false;
		}
	}
	
}
