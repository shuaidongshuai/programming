package _20;

import java.util.Properties;
import java.util.Set;

public class IO_7_Properties¥Ê»° {
	public static void main(String[] args) {
		Properties prop = new Properties();
		prop.setProperty("dong1", "12");
		prop.setProperty("dong2", "22");
		
		prop.setProperty("dong2", "20");
		
		prop.setProperty("dong1",11+"");
		
		Set<String> names = prop.stringPropertyNames();
		for(String s : names)
			System.out.println(s+"  "+prop.getProperty(s));
	}
}
