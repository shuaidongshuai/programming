package _20;

import java.io.File;
import java.io.FilenameFilter;

public class IO_3_file文件列表 {
	public static void main1(String[] args) {
		File[] files = File.listRoots();
		for(File f: files){			//遍历磁盘，盘符
			System.out.println(f);
			
			String[] names = f.list();
			for(String name:names)//遍历每个盘符下的目录  （包含隐藏文件）
				System.out.println(name);
		}
	}
	public static void main2(String[] args) {
		File dir = new File("E:\\programming\\C");
		String[] arr = dir.list(new FilenameFilter(){//过滤器Filter		过滤掉false..只保存true;
			public boolean accept(File dir,String name){
				return name.endsWith(".exe");//如果以.exe结尾那么返回true   否则为false    
			}
		});
		for(String name : arr){
			System.out.println(name);
		}
	}
	public static void main(String[] args) {
		//和上面那个实例不一样。。下面这个是返回的File		文件对象。。上面那个只是返回文件的名字（字符串）
		File dir = new File("E:\\study_materials\\JAVA\\毕向东\\第20天");
		File[] files = dir.listFiles();
		for(File f:files)
			System.out.println(f.getName()+"    大小："+f.length()/1024/1024+"M");//通过文件对象。我们不仅可以获取文件名，而且可以获取大小等
	}
	
}
