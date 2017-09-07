package _25;

import java.awt.Graphics;
import java.awt.Image;
import java.awt.Rectangle;
import java.awt.Toolkit;
/**
 * Ç½Àà
 * @author ¡î¶«¡ï
 *
 */
public class Wall {
	private int x,y,w,h;
	private TankClient tc;
	private static Toolkit tk = Toolkit.getDefaultToolkit();
	private static Image image = tk.getImage(Wall.class.getClassLoader().getResource("images/lawn.jpg"));
	public Wall(int x, int y, int w, int h, TankClient tc) {
		super();
		this.x = x;
		this.y = y;
		this.w = w;
		this.h = h;
		this.tc = tc;
	}
	
	public void draw(Graphics g){
		if(x>150)
		g.drawImage(image, x, y, 100, 80, null);
		else
		g.fillRect(x, y, w, h);
	}
	
	public Rectangle getRect(){
		return new Rectangle(x,y,w,h);
	}
	
}
