package enum枚举;

enum Season{		//声明Season 枚举类型
	春,夏,秋,冬			// 从这可以看出 JAVA 不是用 ASCII 码  而是用 unicode 
}
public class EnumDemo{
	Season season;			//声明变量 season
	public EnumDemo(Season season){			//传递一个 Seson类型的参数
		this.season = season;
	}
	public void saySeason(){			//输出季节
		switch (season){
			case 春:System.out.println("现在是春季.");
			break;
			case 夏:System.out.println("现在是夏季.");
			break;
			case 秋:System.out.println("现在是秋季.");
			break;
			case 冬:System.out.println("现在是冬季.");
			break;
		}
	}
}
//运行
class Test{
	public static void main(String[] args){
		EnumDemo spring = new EnumDemo (Season.春);		//创建 一个新的 对象 实例
		spring.saySeason();								// 调用 saySeason
		EnumDemo summer = new EnumDemo (Season.夏);
		summer.saySeason();
		EnumDemo fall = new EnumDemo (Season.秋);
		fall.saySeason();
		EnumDemo winter = new EnumDemo (Season.冬);
		winter.saySeason();
	}
}
