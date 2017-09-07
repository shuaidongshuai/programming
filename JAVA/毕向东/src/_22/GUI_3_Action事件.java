package _22;

import java.awt.*;
import java.awt.event.*;

public class GUI_3_Action事件 {
	private Frame f;
	private Button but;
	GUI_3_Action事件(){
		init();
	}
	
	public void init(){
		f = new Frame("My Frame");
		
		//对Frame进行计本设置
		f.setBounds(300,100,600,500);
		
		f.setLayout(new FlowLayout());
		but = new Button("my button");
		
		//将组件添加到Frame中
		f.add(but);
		
		//加载窗体事件
		myEvent();
		
		//显示
		f.setVisible(true);
	}
	
	private void myEvent(){
		f.addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent e){
				System.out.println("退出");
				System.exit(0);
			}
		});
		//让按钮具备瑞出程序功能
		/*查阅：Component->Button(子类)->addActionListener(ActionListener l)（方法）->ActionListener（参数）
		 */
		but.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				System.out.println("按钮按下");
			}
		});
	}
	
	public static void main(String[] args) {
		new GUI_3_Action事件();
	}
}
