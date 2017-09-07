package _08;
/*
 * PCI是Peripheral Component Interconnect(外设部件互连标准)的缩写，它是目前个人电脑中使用最为广泛的接口，几乎所有的主板产品上都带有这种插槽
 * 
 * 原来PCI p1 = new NetCard()   这样也叫作多态。。这里接口就相当于了父类
 */
interface PCI{
	public void open();
	public void close();
}

class MainBoard{
	public void run(){
		System.out.println("MainBoard run");
	}
	
	public void usePCI(PCI p){//传进来的是一个接口****任何一个扩展出这个PCI接口的类都可以传进来*****{原来多态是在这里体现的PCI p1 = new NetCard()}
		if(p != null){
			p.open();//调用PCI接口，在子类中实现的方法
			p.close();
		}
	}
}

class NetCard implements PCI{//PCI  扩展出  网卡
	public void open(){								//实现接口中的给出来的方法
		System.out.println("NetCard open");
	}
	public void close(){
		System.out.println("NetCard close");
	}
	public void show(){
		System.out.println("我是网卡");
	}
}
class SoundCard implements PCI{//PCI  扩展出声卡
	public void open(){
		System.out.println("SoundCard open");
	}
	public void close(){
		System.out.println("SoundCard close");
	}
	public void show(){
		System.out.println("我是声卡");
	}
}

public class 多态主板示例 {
	public static void main(String[] args) {
		MainBoard m = new MainBoard();
		m.run();
		m.usePCI(null);//表示目前为止，还没有任何PCI设备
		m.usePCI(new NetCard());
		m.usePCI(new SoundCard());
		
		//下面是自己的扩展
		System.out.println();
		PCI p1 = new NetCard();
		PCI p2 = new SoundCard();
		p1.open();
		p2.open();
		p1.close();
		p2.close();
		//p1.show();  这是错误的 。。  接口中没有  show 这个方法
		new NetCard().show();
		new SoundCard().show();
	}
}
