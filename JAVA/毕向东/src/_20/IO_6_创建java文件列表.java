package _20;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.util.ArrayList;
import java.util.List;

public class IO_6_创建java文件列表 {
	public static void main(String[] args) throws IOException {
		File f = new File("E:\\programming\\JAVA\\毕向东");
		List list = new ArrayList<File>();
		fileToList(f,list);
		System.out.println(list.size());
		writeTofile(list,"E:\\programming\\JAVA\\毕向东\\javaFileList.txt");
	}
	
	public static void fileToList(File dir,List<File> list){
		File[] files = dir.listFiles();
		for(File f : files){
			if(f.isDirectory())
				fileToList(f,list);
			else
				if(f.getName().endsWith(".class"))
				list.add(f);
		}
	}
	
	public static void writeTofile(List<File> file,String s) throws IOException{
		BufferedWriter bufw = new BufferedWriter(new FileWriter(s));
			for(File files : file){
				String path = files.getAbsolutePath();
				bufw.write(path);
				bufw.newLine();
				bufw.flush();
			}
			if(bufw != null)
				bufw.close();
	}
}
