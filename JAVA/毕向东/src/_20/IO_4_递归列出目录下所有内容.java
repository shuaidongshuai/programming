package _20;

import java.io.File;

public class IO_4_递归列出目录下所有内容 {
	public static void main(String[] args) {
		File dir = new File("E:\\study_materials\\JAVA\\达内");
		showDir(dir);
	}
	
	public static void showDir(File dir){
		File[] files = dir.listFiles();
		for(int x = 0;x<files.length;x++){
			System.out.println(files[x]);//打印父目录
			//判断是否是目录
			if(files[x].isDirectory())//递归调用
				showDir(files[x]);
		}
	}
	
}
