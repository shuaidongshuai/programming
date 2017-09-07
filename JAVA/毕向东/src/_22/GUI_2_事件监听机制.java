package _22;

import java.awt.*;
import java.awt.event.*;
/*
 * 事件监听机制特点：
 * 1，事件源
 * 2，事件
 * 3，监听器
 * 4，事件处理
 * 
 * 事件源：就是awt包或者swing包中的那些图形界面组件
 * 
 * 事件：每一个事件源都有自己特有的对应事件和共性事件
 * 
 * 监听器：可以触发某一个事件的动作都已经封装到了监听器中
 * 
 * 以上三者，java都定义好了
 * 
 * 我们要做的就是，对产生的动作进行处理
 */
//因为windowListener的子类WindowAdapter已经实现了WindowListener接口
//并覆盖了之中所有的方法，那么我只要继承WindowAdapter覆盖我需要的方法即可
class MyWin extends WindowAdapter{
	public void windowClosing(WindowEvent e){
//		System.out.println("window closing---"+e.toString());
		System.exit(0);
	}
}
public class GUI_2_事件监听机制 {
	public static void main(String[] args) {
		Frame f = new Frame("hello world");
		f.setLocation(400,200);
		f.setSize(500,400);
		f.setLayout(new FlowLayout());//定义流式布局
		
		Button b = new Button("我是一个按钮");//默认边界式填充
		f.add(b);

		//void addWindowStateListener(WindowStateListener l) 添加指定的窗口状态侦听器，以从此窗口接收窗口事件。 
		f.addWindowListener(new WindowAdapter(){//Adapt适配器（改写）的意思
			public void windowClosing(WindowEvent e){//关闭时调用
		          
				System.out.println("关闭");
				System.exit(0);
			}
			public void windowActivated(WindowEvent e){// 激活窗口时调用 （每当窗口前置，就会触发）
				System.out.println("active");
			}
			public void windowOpened(WindowEvent e){//已打开窗口时调用
				System.out.println("打开了");
			}
			 
		});
		
		f.setVisible(true);
	}
}
