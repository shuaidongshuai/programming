package _13;
/*
 * StringBuffer是字符串缓冲区
 * 
 * 是一个容器
 * 1，而且长度是可以变化的。
 * 2，可以直接操作多个数据类型
 * 3，最终会通过toString 方法变成字符串
 * CURD  	create update read delete
 * 
 * 1.存储
 * 		StringBuffer append()将指定数据作为参数添加到末尾
 * 		StringBuffer insert(index,数据);可以将数据插入到指定index位置
 * 
 * 2.删除
 * 		StringBuffer delete(int start, int end)    移除此序列的子字符串中的字符。 
 * 		StringBuffer deleteCharAt(int index)  移除此序列指定位置的 char。 
 * 3.获取
 * 		 char charAt(int index) 返回此序列中指定索引处的 char 值。 
 * 		 int indexOf(String str) 返回第一次出现的指定子字符串在该字符串中的索引。 
         int indexOf(String str, int fromIndex) 从指定的索引处开始，返回第一次出现的指定子字符串在该字符串中的索引。
         int length();
         String substring(int start,int end)
 * 4.修改
 * 		StringBuffer replace(int start, int end, String str)  使用给定 String 中的字符替换此序列的子字符串中的字符。
 * 		void setCharAt(int index, char ch)      将给定索引处的字符设置为 ch。  
 * 5.反转
 * 		 StringBuffer reverse() 将此字符序列用其反转形式取代。
 * 6.
 *  	 void getChars(int srcBegin, int srcEnd, char[] dst, int dstBegin)  将字符从此序列复制到目标字符数组 dst。 
 * 
 * JDK 1.5 版本之后出现StringBuilder();
 * 
 * StringBuffer是线程同步
 * StringBuilder是线程不同步
 * 
 * 以后开发，建议使用StringBuilder
 * 
 *     public String toString() {
        return getClass().getName() + "@" + Integer.toHexString(hashCode());
    }
 * 
 */
public class Stringbuffer {
	public static void main(String[] args) {
		StringBuffer sb = new StringBuffer();
		sb.append("abc").append(true).append(111);
		sb.insert(1, "东");
		System.out.println(sb);
		
		sb.delete(1, 2);//删除角标 1 --  2 之间的数（但是包含头部不包含尾部）
		System.out.println(sb);
		
		sb.deleteCharAt(0);//删除0号字符
		System.out.println(sb);
		
		sb.delete(0, sb.length());
		System.out.println(sb+"清空了");
		
		sb.append("0123456");
		System.out.println(sb);
//		sb.replace(1,4,"hello dong");//替代
//		System.out.println(sb);
		sb.setCharAt(2, '东');
		System.out.println(sb);
		
		sb.reverse();
		System.out.println(sb);
		
	}
}
