package _22;

import java.awt.*;
/*
 * 创建图形化界面：
 * 1，创建Frame窗体
 * 2，对窗体进行计本设置。比如：位置，大小，布局
 * 3，定义组件
 * 4，将组件通过窗体的add方法添加到窗体中
 * 5，让窗体显示，（setVisible方法）
 */
public class GUI_1 {
	public static void main(String[] args) {
		Frame f = new Frame("hello world");
		f.setLocation(400,200);
		f.setSize(500,400);
		f.setLayout(new FlowLayout());//定义流式布局
		
		Button b = new Button("我是一个按钮");//默认边界式填充
		f.add(b);
		
		f.setVisible(true);
		
	}
}
