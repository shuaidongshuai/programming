package _09;
/*题目：
 * 毕老师用电脑上课
 * 
 * prelect讲课
 * restart重启
 */
class BlueScreenException extends Exception{//当电脑出现蓝屏，异常时。老师能处理
	BlueScreenException(String message){
		super(message);
	}
}
class ComputerSmokeException extends Exception{//当电脑冒烟，异常时。老师不能处理
	ComputerSmokeException(String message){
			super(message);
		}
}
class NoPlanException extends Exception{		//老师不能处理时，抛出去的异常
	NoPlanException(String message){
		super(message);
	}
}
class Computer{
	public int state = 3;//1代表正常												把这  换成  1 2 3  看看效果
	public void run()throws BlueScreenException,ComputerSmokeException{
		if(state == 2)
			throw new BlueScreenException("电脑蓝屏了");
		if(state == 3)
			throw new ComputerSmokeException("电脑冒烟了");//把电脑冒烟抛出去
		
		System.out.println("电脑运行");
	}
	
	public void restart() throws BlueScreenException, ComputerSmokeException{//因为这里面有run();方法，所以必须加上throws(当发现异常就抛出异常)
		System.out.println("重启电脑");
		state = 1;//表示重启后正常
		run();
	}
}
class Teacher{
	private String name;
	private Computer c;
	Teacher(String name,Computer c){//为了方便，我们除了传老师的名字，还传进来现在电脑现在的状态
		this.name = name;
		this.c = c;
	}
	
	public void prelect()throws NoPlanException, BlueScreenException, ComputerSmokeException{//老师无法处理就抛给   父类、、、由于调用了restart
		try {																	//restart中有run();所以得加上BlueScreenException, ComputerSmokeException
			c.run();				//电脑运行时可能会出错
		} catch (BlueScreenException e) {
			System.out.println(e.getMessage());
			System.out.println(name+"说：小意思我来解决");
			c.restart();					//蓝屏，老师可以处理（重启）
		}catch (ComputerSmokeException e) {
			throw new NoPlanException("课时无法继续,因为："+e.getMessage());//老师无法处理，就需要抛出（课时无法继续,因为：电脑冒烟了）
		}												//e.getMessage()获取课时无法继续的原因：电脑冒烟了
		
		System.out.println("老师开始讲课");
	}
}

public class 异常练习 {
	public static void main(String[] args) throws BlueScreenException, ComputerSmokeException{//t.prelect中不止NoPlanException这一个异常
		Computer c = new Computer();//对于BlueScreenException, ComputerSmokeException这两个异常，校长选择抛出（校长不懂电脑）。校长只处理NoPlanException异常
		
		for(int i=1;i<4;i++){
			System.out.println("The state of the Computer is :"+i);
			c.state = i;
			Teacher t = new Teacher("毕老师",c);
			try {
				t.prelect();
			} catch (NoPlanException e) {
				System.out.println("老师说："+e.getMessage());
				System.out.println("校长：换老师或放假");//这里我们假设   校长让老师放假  或  换老师
			}
		}

	}
}
