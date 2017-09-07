package _16;

import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;

/*
 * "abcdabcdef"获取该字符串的字母出现的次数
 * 希望打印结果 ： a(1)c(2)-----
 * 
 * 思路：
 * 1，将字符串转换成字符数组，因为要对每一个字母进行操作
 * 2，定义一个map集合，因为打印结果的字母有顺序，所以使用treemap集合
 * 3，遍历字符数组
 * 		将每一个字符作为键值去查map集合
 * 		如果范围null，将字母和1存入
 * 		如果返回不是null，获取该次数，并自增，然后将该字母和自增后的次数存入map集合中
 * 4，强map集合中的数据变成指定的字符串形式返回
 * 
 */
public class map_4_练习 {
	public static void main(String[] args) {
//		charCount("abcdabcd.dong");
		String s = charCount("abcdabcd.dong");
		System.out.println(s);
	}
	
	public static String charCount(String str){
		char[] chs = str.toCharArray();
		
		TreeMap<Character,Integer> tm = new TreeMap<Character,Integer>();
		
		for(int x=0;x<chs.length;x++){
			//根据键值（字符）	获取值（字符对应的次数）
			Integer value = tm.get(chs[x]);
			
			if(value==null)
				value = 0;;
			value++;//为null value = 1  不为 null 自增  1
			
			tm.put(chs[x], value);
		}
		System.out.println(tm);
		//定义一个缓冲区，他可以存入任何东西
		StringBuilder sb = new StringBuilder();
		
		/*第一种取法
		Set<Character> keyset = tm.keySet();
		for(Iterator<Character> it = keyset.iterator();it.hasNext();){
			char key = it.next();
			int value = tm.get(key);
			sb.append(key+"("+value+")");
		}*/
		//第二种
		Set<Map.Entry<Character,Integer>> entryset = tm.entrySet();
		for(Iterator<Map.Entry<Character,Integer>> it = entryset.iterator();it.hasNext();){
			Map.Entry<Character,Integer> me = it.next();
			char key = me.getKey();
			int value = me.getValue();
			sb.append(key+"("+value+")");
		}
		
		return sb.toString();
	}
	
}
/*类 Character所有已实现的接口： 
Serializable, Comparable<Character> 

 */
