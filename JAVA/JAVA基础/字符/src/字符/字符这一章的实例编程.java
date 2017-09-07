package 字符;
import java.util.*;
public class 字符这一章的实例编程 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		while(true){
		String originalUserName = "12";
		String orginalPassword = "12";
		//进行输入
		Scanner s = new Scanner(System.in);
		String name = s.nextLine();
		String Pwd = s.nextLine();
		if(!name.equals(originalUserName)){
			System.out.println("无用户\n");
			continue;
		}
		if(!Pwd.equals(orginalPassword)){
			System.out.println("密码错误\n");
			continue;
		}
		System.out.println("通过");		
		}
	}

}
