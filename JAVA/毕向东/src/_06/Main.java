
package _06;//如果要在命令行中运行这个程序，这一行必须注释掉

/*public class Main {
	public static void main(String[] args) {
		for(int i=0;i<args.length;i++)
			System.out.println(args[i]);
	}
}*/

//用下面这样的方法  就可以不用每次都在命令行中打印
public class Main {
public static void main(String[] args) {
	String[] arr = {"chen","ming","dong"};
	Maintest.main(arr);
}
}
class Maintest{
	public static void main(String[] args) {
		for(int i=0;i<args.length;i++)
			System.out.println(args[i]);
	}
}
