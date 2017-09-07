package _09;
/*题目：
 * 毕老师用电脑上课
 * 
 * prelect讲课
 * restart重启
 */
class Teacher1{
	private String name;
	private Computer c;
	Teacher1(String name,Computer c){
		this.name = name;
		this.c = c;
	}
	
	public void prelect()throws BlueScreenException, ComputerSmokeException{//老师无法处理就抛给   父类、、、由于调用了restart
		try {																	//restart中有run();所以得加上BlueScreenException, ComputerSmokeException
			c.run();				//电脑运行时可能会出错
		} catch (BlueScreenException e) {
			throw new BlueScreenException("课时无法继续,因为："+e.getMessage());
		}catch (ComputerSmokeException e) {
			throw new ComputerSmokeException("课时无法继续,因为："+e.getMessage());//老师无法处理，就需要抛出（课时无法继续,因为：电脑冒烟了）
		}												
		System.out.println("老师开始讲课");
	}
	
}

public class 异常练习升级版 {
	public static void main(String[] args) throws BlueScreenException, ComputerSmokeException{
		Computer c = new Computer();
		
		for(int i=1;i<4;i++){
			System.out.println("The state of the Computer is :"+i);
			c.state = i;
			Teacher1 t = new Teacher1("毕老师",c);
			try {
					t.prelect();
				}catch (ComputerSmokeException e) {
				System.out.println("老师说："+e.getMessage());
				System.out.println("校长：换老师或放假");//这里我们假设   校长让老师放假  或  换老师
			}catch (BlueScreenException e){
				System.out.println("老师说："+e.getMessage());
				System.out.println("校长说：你重启啊！笨！");
				c.restart();
				System.out.println("老师开始讲课");
			}
		}

	}
}
