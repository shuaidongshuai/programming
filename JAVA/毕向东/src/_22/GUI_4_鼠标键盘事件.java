package _22;

import java.awt.*;
import java.awt.event.*;
/*
 * Component
 */
public class GUI_4_鼠标键盘事件 {
	private Frame f;
	private Button but1,but2;
	private TextField tf;
	GUI_4_鼠标键盘事件(){
		init();
	}
	
	public void init(){
		f = new Frame("My Frame");
		
		//对Frame进行计本设置
		f.setBounds(300,100,600,500);
		
		f.setLayout(new FlowLayout());
		but1 = new Button("my button1");
		but2 = new Button("my button2");
		tf   = new TextField(20);
		//将组件添加到Frame中
		f.add(but1);
		f.add(but2);
		f.add(tf);
		
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
		/*查阅：Component-> void addMouseListener(MouseListener l) 添加指定的鼠标侦听器，以接收发自此组件的鼠标事件 
		 * 		->MouseListener->MouseAdapter(抽象类)
		 * 					  void mouseEntered(MouseEvent e)           鼠标进入到组件上时调用。 
		 * 					  void mousePressed(MouseEvent e)           鼠标按键在组件上按下时调用。 调用。
 							  void mouseWheelMoved(MouseWheelEvent e)    鼠标滚轮旋转时调用。
 			->MouseEvent->    int getClickCount()       返回与此事件关联的鼠标单击次数。
     
		 */
		but1.addMouseListener(new MouseAdapter(){
//			public void mouseEntered(MouseEvent e){
//				System.out.println("鼠标放上来了");
//			}
			public void mousePressed(MouseEvent e){
				if(e.getClickCount() == 3)
					System.out.println("三击动作---");
				else if(e.getClickCount() == 2)
				System.out.println("双击动作");
			}
			public void mouseWheelMoved(MouseWheelEvent e){
				System.out.println("鼠标滚轮旋转时调用。");
			}
		});
		but1.addActionListener(new ActionListener(){//和上面的区别就是，方面必须是鼠标操作了按钮，这个处了鼠标，键盘也可以是按钮活动
			public void actionPerformed(ActionEvent e){
				System.out.println("按钮活动了");
			}
		});
		//给but2天假一个键盘监听
		but2.addKeyListener(new KeyAdapter(){
			public void keyPressed(KeyEvent e){
				System.out.println(KeyEvent.getKeyText(e.getKeyCode())+"      "+e.getKeyCode());
				if(e.getKeyCode() == KeyEvent.VK_ENTER && e.isControlDown())// boolean isControlDown()  返回 Control 修饰符在此事件上是为 down 
					System.exit(0);
			}
		});
		
		//添加文本框键盘监听
		tf.addKeyListener(new KeyAdapter(){
			public void keyPressed(KeyEvent e){
				int code = e.getKeyCode();
				if(!(code>=KeyEvent.VK_0 && code<=KeyEvent.VK_9 || code>=KeyEvent.VK_NUMPAD0 && code<=KeyEvent.VK_NUMPAD9)){//只允许输入0 - 9
					System.out.println(KeyEvent.getKeyText(code)+"     非法");
					e.consume();//void consume() 使用此事件，以便不会按照默认的方式由产生此事件的源代码来处理此事件。 
				}
			}
		});
	}
	
	public static void main(String[] args) {
		new GUI_4_鼠标键盘事件();
	}
}
