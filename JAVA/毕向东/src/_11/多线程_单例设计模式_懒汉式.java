package _11;
/*
 * 懒汉式延迟加载
 * 在多线程中，会出现安全隐患
 * 使用同步代码块解决
 */
class Single{
	private static Single s = null;
	private Single(){}
	public static Single getInstance(){
		if(s==null){
			synchronized(Single.class){//使用的锁是，该类所属的字节码对象
				if(s==null)
					s = new Single();
			}
		}
		return s;
	}
}
public class 多线程_单例设计模式_懒汉式 {

}
