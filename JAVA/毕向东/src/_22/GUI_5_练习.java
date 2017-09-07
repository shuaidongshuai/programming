package _22;

import java.awt.Button;
import java.awt.Dialog;
import java.awt.FlowLayout;
import java.awt.Frame;
import java.awt.Label;
import java.awt.TextArea;
import java.awt.TextField;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.File;

public class GUI_5_练习 {
	private Frame f;		//框架
	private TextField tf;	//文本框
	private TextArea ta;	//有多行的文本框(文本区)
	private Button but;		//按钮
	private Dialog d ;		//对话框
	private Button okButton;//对话框中的按钮
	private Label lab;		//标签（给对话框加文字的）
	GUI_5_练习(){
		init();
	}
	public void init(){
		f = new Frame("My window");
		//基本设置
		f.setBounds(300,100,600,450);//设置  框架，x , y 坐标   和   长 宽
		f.setLayout(new FlowLayout());//流式布局
		tf = new TextField(50);//文本框
		ta = new TextArea(18,70);//长18  70行   的文本框  
		but = new Button("转到");//按钮
		
		d = new Dialog(f,"提示信息",true);//定义一个对话框，   第一个参数是关联  Frame的，第三个参数如果为true那么有Dialog对话框时，不能动Frame，False就可以动
		d.setBounds(500,300,350,100);//对话框中的位置+大小
		d.setLayout(new FlowLayout());//流式布局
		lab = new Label(); //组件里面不能直接写文本，要用标签
		okButton = new Button("  确定    ");//对话框中的按钮
		
		//添加组件
		f.add(tf);//添加到Frame
		f.add(but);
		f.add(ta);
		
		d.add(lab);//添加到Dialog
		d.add(okButton);
		
		//添加窗口事件
		myEvent();
		
		//可见
		f.setVisible(true);
	}
	
	private void myEvent(){
		//实现Frame框架 的关闭功能
		f.addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent e){
				System.out.println("退出");
				System.exit(0);
			}
		});
		//实现Dialog对话框的关闭功能
		d.addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent e){
				d.setVisible(false);
			}
		});
		//实现Dialog对话框按键      按下时的功能（使Dialog对话框消失）。。这个是活动的，所以键盘敲入也可以
		okButton.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				d.setVisible(false);
			}
		});
		//设置文本框   按键功能
		tf.addKeyListener(new KeyAdapter(){
			public void keyPressed(KeyEvent e){
				if(e.getKeyCode() == e.VK_ENTER)
					showDir();
			}
		});
		//设置 ，，按钮活动时的功能
		but.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				showDir();
			}
		});
	}
	private void showDir(){
		String dirPath = tf.getText();//获取文本内容
		
		File dir = new File(dirPath);//把文本内容转化为路径
		if(dir.exists() && dir.isDirectory()){//判断路径是否存在  且 有这个目录
			ta.setText("");//清空文本
			String[] names = dir.list();//获取该路径下的列表
			for(String name : names){//遍历列表
				ta.append(name+"\n");//以追加的方式写入
			}
		}
		else{//如果没有目录或输入错误
			String info = "您输入的信息有误:"+dirPath+"请重输";
			lab.setText(info);
			d.setVisible(true);
		}
		tf.setText("");//每次输入完文本框，自动清空
	}
	public static void main(String[] args) {
		new GUI_5_练习();
	}
}
/*	Window    ->    void addWindowListener(WindowListener l) 添加指定的窗口侦听器，以从此窗口接收窗口事件。
              ->    WindowListener   ->     WindowAdapter 
              ->	void windowClosing(WindowEvent e)  窗口正处在关闭过程中时调用。 
              
	Button    ->	void addActionListener(ActionListener l)  添加指定的动作侦听器，以接收发自此按钮的动作事件。 
			  ->	ActionListener    ->    void actionPerformed(ActionEvent e)  发生操作时调用。
			  
	Component ->    void addKeyListener(KeyListener l)   添加指定的按键侦听器，以接收发自此组件的按键事件。
			  ->	KeyListener       ->	KeyAdapter
			  ->	void keyPressed(KeyEvent e)    按下某个键时调用此方法。 

 
           
 */
