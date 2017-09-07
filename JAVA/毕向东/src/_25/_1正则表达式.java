package _25;
/*
 * 正则表达式：符合一定规则的表达式
 * 		作用：用于专门操作字符串
 * 		特点：用一些特定的符号来表示一些代码操作
 * 		好处：可以简化对字符串的复杂操作
 * 
 * 具体操作
 * 1，匹配：String matches方法
 * 
 * 
 */
public class _1正则表达式 {
	public static void main(String[] args) {
		//qq();
		checkqq();
	}
	/*
	 * 对QQ号进行校验
	 * 要求：5~15 0不能开头，只能是数字
	 */
	public static void qq(){
		String q = "a12345";
		int len = q.length();
		
		if(len>=5 && len<=15){
			if(!q.startsWith("0")){
				try {
					long l = Long.parseLong(q);
				} catch (NumberFormatException e) {
//					throw new NumberFormatException("出现非法字符===");
					System.out.println("出现非法字符===");
				}
				/*char[] arr = q.toCharArray();
				boolean flag = true;
				for(int x = 0;x<arr.length;x++){
					
					if(arr[x]<'0' || arr[x] >'9'){
						flag = false;
						break;
					}
				}
				if(flag)
					System.out.println("qq:"+q);
				else
					System.out.println("非法字符");*/
			}
			else
				System.out.println("不能以0开头");
		}
		else
		System.out.println("长度错误");
	}
	
	public static void checkqq(){
		String qq = "2a3314";
		boolean f = qq.matches("[0-9][1-9]{4,14}");
		if(f)
			System.out.println("qq:"+qq);
		else
			System.out.println("不合法");
	}
}
