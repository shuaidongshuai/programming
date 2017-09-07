package _13;
/*
 * 查找一个字符串中    某一个子串的个数
 */
public class String_练习2 {
	public static void main(String[] args) {
		String s = " hello java xxx yyy xx xx yxy ";//在索引的时候   xxx  算一种子串，，感觉有问题，到底xxx算一个子串还是两个，还是不算子串
		System.out.println(s.indexOf("xx"));
		System.out.println(getSubCount(s,"xx"));
	}
	
	static int getSubCount(String str,String sub){
		int index = 0;
		int count = 0;
		while((index = str.indexOf(sub, index))!= -1){
			count++;
			index = index + sub.length();
		}
		return count;
	}
}
