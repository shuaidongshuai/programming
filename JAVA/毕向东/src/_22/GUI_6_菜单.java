package _22;

import java.awt.FileDialog;
import java.awt.Frame;
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
public class GUI_6_菜单 {
	private Frame f;
	private MenuBar bar;
	private Menu fileMenu;
	private MenuItem openItem,saveItem,closeItem;//Item项目，条款
	private TextArea ta;
	private FileDialog openDia,saveDia;
	private File file;
	GUI_6_菜单(){
		init();
	}
	public void init(){
		f = new Frame("my window");
		f.setBounds(300,100,650,600);
//		f.setLayout(new FlowLayout());
		
		bar = new MenuBar();//创建菜单栏
		fileMenu = new Menu("文件");//创建菜单项
		openItem = new MenuItem("打开");
		saveItem = new MenuItem("保存");
		closeItem = new MenuItem("退出");//创建菜单条
		ta = new TextArea();
		
		f.setMenuBar(bar);//在框架中添加菜单栏
		f.add(ta);
		bar.add(fileMenu);//在菜单栏里面放菜单项
		fileMenu.add(openItem);//在菜单项里面方放（子条目）
		fileMenu.add(saveItem);//在菜单项里面方放（子条目）
		fileMenu.add(closeItem);//在菜单项里面方放close（子条目）
		
		
		openDia = new FileDialog(f,"我要打开",FileDialog.LOAD);
		saveDia = new FileDialog(f,"我要保存",FileDialog.SAVE);
		
		myEvent();
		
		f.setVisible(true);
	}
	private void myEvent(){
		f.addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent e){
				System.out.println("退出");
				System.exit(0);
			}
		});
		
		openItem.addActionListener(new ActionListener(){//添加动作监听，动作监听
			public void actionPerformed(ActionEvent e){//动作执行（Perform），表演
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
					while((line = bufr.readLine())!=null)//从BufferedReader中读取一行数据
						ta.append(line+"\n");//打印到文本区
					bufr.close();//关闭BufferedReader
					
				} catch (IOException e2) {
					// TODO: handle exception
					throw new RuntimeException("读取失败");
				}
			}
		});
		saveItem.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				if(file==null){
					saveDia.setVisible(true);
					
					String dirPath = saveDia.getDirectory();
					String fileName = saveDia.getFile();
					if(dirPath == null || fileName == null)
						return ;
					file = new File(dirPath,fileName);//创建一个文件对象
				}
				try {
					BufferedWriter bufw = new BufferedWriter(new FileWriter(file));//将文本写入字符输出流
					String text = ta.getText();//获取文本区的字符串
					bufw.write(text);//向文件中写入文本区的字符串
					bufw.close();
				} catch (IOException e2) {
					throw new RuntimeException();
				}
			}
		});
		
		
		closeItem.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				System.exit(0);
			}
		});
	}

	
	public static void main(String[] args) {
		new GUI_6_菜单();
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
