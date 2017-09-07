package 字符;

public class StringBuffer类 {
	public static void main(String [] args){
		//声明一个StringBuffer 变量 sb 
		StringBuffer sb = new StringBuffer();
		
		//append 是一个函数  ：添加参数到  StringBuffer 变量中 
		sb.append("我很");
		sb.append("爱你");
		sb.append("dong");
		
		// toString 是一个函数  （返回一个包含在StringBuffer中的字符序列）
		System.out.println(sb.toString());
		// 尝试了一下  不要 toString 也可以输出
		System.out.println(sb);
	}
}
// StringBuffer 和 String 的比较

/* StringBuffer 有产生的对象  默认有16 个字符的长度 ，内容和长度都可以改变，！！可以超出容纳量！！有伸缩性（而String是固定的）*/
