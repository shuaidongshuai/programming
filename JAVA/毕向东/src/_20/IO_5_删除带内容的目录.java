package _20;

import java.io.File;

/*
 * windows中
 * 必须从里往外删
 */
public class IO_5_删除带内容的目录 {
	public static void main(String[] args) {
		File dir = new File("D:\\QMDownload");
		removeDir(dir);
	}
	public static void removeDir(File dir){
		File[] files = dir.listFiles();
		for(int i=0;i<files.length;i++){
			if(files[i].isDirectory())
				removeDir(files[i]);
			else
				System.out.println(files[i].toString()+"  file  "+files[i].delete());
		}
		System.out.println(dir+"  dir  "+dir.delete());
	}
	
}
