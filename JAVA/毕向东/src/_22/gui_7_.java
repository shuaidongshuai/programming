package _22;

import java.awt.Button;
import java.awt.Color;
import java.awt.Dialog;
import java.awt.FileDialog;
import java.awt.FlowLayout;
import java.awt.Frame;
import java.awt.Label;
import java.awt.Menu;
import java.awt.MenuBar;
import java.awt.MenuItem;
import java.awt.TextArea;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

/*
 * MenuBar菜单栏		为了将该菜单栏与 Frame 对象关联，可以调用该框架的 setMenuBar 方法
 */
public class gui_7_ {
	private Frame f;
	private MenuBar bar;
	private Menu fileMenu,fileMenu2,fileMenu3,fileMenu4;
	private MenuItem openItem,saveItem,closeItem1,closeItem2,haha;//Item项目，条款
	private TextArea ta;
	private FileDialog openDia,saveDia;
	private File file;
	private Dialog Dia;
	private Label lab;
	private Button okButton;
	gui_7_(){
		init();
	}
	public void init(){
		f = new Frame("自己做的记事本，功能还不全，请见谅............只能简单的打开，保存，关闭.txt文件★★★★★注意是.txt文件");
		f.setBounds(300,100,900,550);
//		f.setLayout(new FlowLayout());
		
		bar = new MenuBar();//创建菜单栏
		fileMenu = new Menu(" 文件       ");//创建菜单项
		fileMenu2 = new Menu("这里啥都没有呦");
		fileMenu3 = new Menu("给你说了啥都没有还不信");
		fileMenu4 = new Menu("被骗了吧");
		openItem = new MenuItem("打开☆ ");
		saveItem = new MenuItem("保存★ ");
		closeItem1 = new MenuItem("退出℃ ");//创建菜单条
		closeItem2 = new MenuItem("陈明东");//创建菜单条
		haha = new MenuItem("O(∩_∩)O哈哈~");
		ta = new TextArea();
		Dia = new Dialog(f,"确定保存到当前文件里面么",true);
		lab = new Label("O(∩_∩)O"); //组件里面不能直接写文本，要用标签
		okButton = new Button("  确定    ");//对话框中的按钮
		
		f.setMenuBar(bar);//在框架中添加菜单栏
		f.add(ta);
		bar.add(fileMenu);//在菜单栏里面放菜单项
		bar.add(fileMenu2);
		fileMenu.add(openItem);//在菜单项里面方放（子条目）
		fileMenu.add(saveItem);//在菜单项里面方放（子条目）
		fileMenu.add(closeItem1);//在菜单项里面方放close（子条目）
		fileMenu2.add(fileMenu3);
		fileMenu2.add(closeItem2);
		fileMenu3.add(fileMenu4);
		fileMenu4.add(haha);
		Dia.add(lab);//添加到Dialog
		Dia.add(okButton);
		Dia.setBounds(500,300,300,100);//对话框中的位置+大小
		Dia.setLayout(new FlowLayout());//流式布局
		
		openDia = new FileDialog(f,"你要打开啥。。。。。搞快点。。。。东哥等着我捶背",FileDialog.LOAD);//创建  对象（文件打开对象）
		saveDia = new FileDialog(f,"快点保存。。。。东哥等着我捏腿",FileDialog.SAVE);//创建 对象（文件保存对象）  都是调用windows资源
		myEvent();
		
//		f.setBackground(Color.BLUE);
		f.setVisible(true);
	}
	//当触发框架   	X 	 时
	private void myEvent(){
		f.addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent e){
				System.out.println("退出");
				System.exit(0);
			}
		});
		//当触发  okButton时
		okButton.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				//把   文本区中的内容  写入到 文件中
				try {
					BufferedWriter bufw = new BufferedWriter(new FileWriter(file));//将文本写入字符输出流
					String text = ta.getText();//获取文本区的字符串
					bufw.write(text);//向文件中写入文本区的字符串
					bufw.close();
				} catch (IOException e2) {
					throw new RuntimeException();
				}
				Dia.setVisible(false);		//然后在关闭   对话框，，最好不要把这句话  放到最前面，因为，如果没有保存好，那么这个对话框就不会消失，减少BUG
			}
		});
		//把对话框 的		X		按钮进行设置（当按下时就关闭）
		Dia.addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent e){
				Dia.setVisible(false);
			}
		});
		//点击打开时触发的动作
		openItem.addActionListener(new ActionListener(){//添加动作监听，动作监听
			public void actionPerformed(ActionEvent e){//动作执行（Perform）
				openDia.setVisible(true);//打开对话框，java已经提供好了FileDialog类
				String dirPath = openDia.getDirectory();//记录目录
				String fileName = openDia.getFile();//记录文件名
				if(dirPath == null || fileName == null)
					return ;
				ta.setText("");
				file = new File(dirPath,fileName);//创建一个文件对象
				try {
					BufferedReader bufr = new BufferedReader(new FileReader(file));//从字符输入流中读取文本
					String line = null;
					int n = 0;
					while((line = bufr.readLine())!=null && n++<200)//从BufferedReader中读取一行数据
						ta.append(line+"\r\n");//打印到文本区
					
					bufr.close();//关闭BufferedReader
				} catch (IOException e2) {
					throw new RuntimeException("读取失败");
				}
			}
		});
		//点击保存时触发的动作
		saveItem.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				if(file==null){							//如果这个程序还没有new 一个 File 那么就会打开 <保存对话框>
					saveDia.setVisible(true);			//显示保存对话框
					String dirPath = saveDia.getDirectory();
					String fileName = saveDia.getFile();
					if(dirPath == null || fileName == null)// 那么就获取当前路径和文件名
						return ;//如果点了保存  然后又点X  那么就没有路径 
					file = new File(dirPath,fileName);//然后 new 一个 file
				}
				Dia.setVisible(true);					//不管程序是否有一个file   都会显示“是否保存”  按 X 就相当于没有触发过save，按确定就跳到okButton中去执行
			}
		});
		//点击关闭时触发的动作
		closeItem1.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				System.exit(0);
			}
		});
	}
	public static void main(String[] args) {
		new gui_7_();
	}
}
/*	MenuItem -> void addActionListener(ActionListener l) 添加指定的动作侦听器，以从此菜单项接收动作事件
    Dialog	 -> FileDialog 
          
    FileReader 用于读取字符流。要读取原始字节流，请考虑使用 FileInputStream。
    BufferedReader从字符输入流中读取文本
    
	public String readLine()
              throws IOException读取一个文本行。通过下列字符之一即可认为某行已终止：换行 ('\n')、回车 ('\r') 或回车后直接跟着换行。
                返回：包含该行内容的字符串，不包含任何行终止符，如果已到达流末尾，则返回 null
 
 */
