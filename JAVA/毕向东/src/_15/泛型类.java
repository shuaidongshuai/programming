package _15;
/*
 * 什么时候定义泛型类？
 * 当类中要操作的引用数据类型不确定的时候
 * 早起定义Object来完成扩展
 * 现在定义泛型来完成扩展
 */
class Worker{
	
}
class Tool{
	private Object obj;

	public Object getObj() {
		return obj;
	}

	public void setObj(Object obj) {
		this.obj = obj;
	}

}
//泛型类
class Utils<QQ>{
	private QQ q;

	public QQ getQ() {
		return q;
	}

	public void setQ(QQ q) {
		this.q = q;
	}
	
}
public class 泛型类 {
	public static void main(String[] args) {
//		Tool t = new Tool();
//		t.setObj(new Worker());
//		Worker w = (Worker)t.getObj();
		
		Utils<Worker> u = new Utils<Worker>();
		u.setQ(new Worker());
		Worker w = u.getQ();
	}
}
