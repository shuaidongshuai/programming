package _18;

import java.io.IOException;

/*
 * Runtime
 * 不可以new 对象
 * 而且该类中还有非静态方法
 * 说明该类肯定会提供了方法获取本类对象，而且该方法是静态的
 * 
 * 该类使用了单例设计模式
 */
public class _Runtime {
	public static void main(String[] args) throws Exception {
		Runtime r = Runtime.getRuntime();
//		r.exec("E:\\programming\\JAVA\\exe文件\\file\\东东专用记事本.exe");
		r.exec("notepad.exe E:\\programming\\JAVA\\毕向东\\src\\_18\\_Runtime.java");
	}
}
