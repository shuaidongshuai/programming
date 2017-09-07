package _13;
/*
 * 获取两个字符串中最大相同的子串
 * 
 * 但是下面这个程序不能处理，同时有两个或两个以上的最大相同子串（只能返回靠前的最大子串）。。。其实要改也很好改，主要是思想
 */
public class String_练习3 {
	public static void main(String[] args) {
		String s1 = "dfsahellodongfdsjoa";
		String s2 = "helloaswedong";
		System.out.println("最大子串"+getMaxSubString(s1, s2));
	}
	
	public static String getMaxSubString(String s1,String s2){
		String max,min;
		max = (s1.length()>s2.length()?s1:s2);
		min = (max == s1)?s2:s1;
		
		for(int i = 0; i<min.length(); i++){
			for(int j = min.length()-i , z = 0; j<=min.length();j++,z++){
				String temp = min.substring(z,j);
				System.out.println(temp);
				if(max.contains(temp))
					return temp;
			}
		}
		return "";
	}
}
