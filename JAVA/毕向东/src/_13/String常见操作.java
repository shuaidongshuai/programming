package _13;

import javax.swing.plaf.synth.SynthSeparatorUI;

/*
 * 1，获取
 * 		1.1   int length()获取长度
 * 		1.2   char At(int index)	返回指定索引处的 char 值。
 * 		1.3   int indexOf(int ch) 返回指定字符在此字符串中第一次出现处的索引。
 * 			  int indexOf(int ch, int fromIndex) 返回在此字符串中第一次出现指定字符处的索引，从指定的索引开始搜索。
 * 			  int indexOf(String str)  返回指定子字符串在此字符串中第一次出现处的索引。
 * 			  int indexOf(String str, int fromIndex) 返回指定子字符串在此字符串中第一次出现处的索引，从指定的索引开始。
 *  		  int lastIndexOf(int ch)   返回指定字符在此字符串中最后一次出现处的索引。
 *  2.判断
 *  	2.1	boolean contains(CharSequence s) 当且仅当此字符串包含指定的 char 值序列时，返回 true。 
 *  	2.2 boolean isEmpty() 当且仅当 length() 为 0 时返回 true
 *  	2.3 boolean startsWith(String prefix)   测试此字符串是否以指定的前缀开始。 
 *  	2.4 boolean endsWith(String suffix)   测试此字符串是否以指定的后缀结束。
 *  	2.5 boolean equals(Object anObject)   将此字符串与指定的对象比较
 *  	2.6 boolean equalsIgnoreCase(String anotherString) 将此 String 与另一个 String 比较，不考虑大小写。 
 *  3.转换
 *  	3.1 String(char[] value)  分配一个新的 String，使其表示字符数组参数中当前包含的字符序列。
 *  		String(char[] value, int offset, int count) 分配一个新的 String，它包含取自字符数组参数一个子数组的字符。
          	static String copyValueOf(char[] data) 返回指定数组中表示该字符序列的 String。 
 *  	3.2
 *  	3.3
 *  	3.4
 *  
 */
public class String常见操作 {
	public static void main(String[] args) {
		int[] a ={1,2,3,4};
		String str = "abcdefg abcd";
		System.out.println(str);
		System.out.println(str.length());
		System.out.println(a.length);
		
		//根据索引获取字符
		System.out.println(str.charAt(4));
		
		//根据字符获取索引
		System.out.println(str.indexOf('a'));
		System.out.println(str.indexOf('a',3));
		System.out.println(str.indexOf('m'));//没有找到返回-1
		
		//反向索引一个字符出现位置
		System.out.println(str.lastIndexOf('a'));//虽然是反向索引，但是返回值，还是他正向的位置
		
		System.out.println(str.startsWith("abc"));
		System.out.println(str.endsWith("cd"));
		System.out.println(str.contains("g "));
		
		if(str.indexOf("aa")== -1)
			System.out.println("哈哈");
		if(str.contains("aa")==false)
			System.out.println("呵呵");
		
		char[] arr = {'a','b','c','d'};
		System.out.println(arr);
		String s = new String(arr);
		System.out.println(s);
		String s1 = new String(arr,1,2);
		System.out.println(s1);
		
		String s2 = "dong";
		char[] arr2 = s2.toCharArray();
		for(int i=0;i<arr2.length;i++)
			System.out.println("arr"+i+" = "+arr[i]);
		
		s2 = "hello java";
		String s3 = s2.replace('a', 'p');
		System.out.println(s3);
		
		s3 = s2.replace("java", "word");
		System.out.println(s3);
		
		
		//下面两种方法切割
		String s4 = "张三，李四，王五";
		String[] s5 = s4.split("，");//切割
		for(int i=0;i<s5.length;i++)
			System.out.println(s5[i]);
		
		String[] ss = new String[3];
		int x = s4.indexOf("，");
		int y = s4.indexOf("，",x);
		int z = s4.indexOf("，",y);
		ss[0] = s4.substring(0,x);
		ss[1] = s4.substring(x,y);
		ss[2] = s4.substring(y,z);
		for(int i=0;i<ss.length;i++)
			System.out.println(s5[i]);
		
		String s6 = "abcdef";
		System.out.println(s6.substring(2));
		System.out.println(s6.substring(2,4));//第二个参数  包含头，不包含尾、。。返回的是   从角标  2--3 的字符
		
		String s7 = "   Hello , java    ";
		System.out.println(s7.toLowerCase());//小写
		System.out.println(s7.toUpperCase());//转换成大写
		System.out.println(s7.trim());//去掉两端空格
		
		String s8 = "add";
		String s9 = "aaa";
		String s10 = "a1";// 1 的 ASCII码  49  a 的 ASCII码 97
		String s11 = "ADD";
		System.out.println(s8.compareTo(s9));
		System.out.println(s10.compareTo(s9));// ‘1’  -  ‘a'  =  -48
		System.out.println(s8.compareToIgnoreCase(s11));//忽略大小写比较
		char c = 49;
		System.out.println(c);
	}
}
