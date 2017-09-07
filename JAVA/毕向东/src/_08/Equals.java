package _08;
class Demo{
	
}
class Demo2{
	int num;
	Demo2(int num){
		this.num = num;
	}
	
    public boolean equals(Object obj) {
        //return (this == obj);
    	if(!(obj instanceof Demo2))
    		return false;
    	Demo2 d = (Demo2)obj;
    	return this.num == d.num;
    }
}
public class Equals {
	public static void main(String[] args) {
		Demo d = new Demo();
		Demo d2 = new Demo();
		System.out.println(d.equals(d));
		System.out.println(d.equals(d2));//equals比较的是地址
		
		Demo2 d3 = new Demo2(4);
		Demo2 d4 = new Demo2(4);
		Demo2 d5 = new Demo2(5);
		System.out.println(d3.equals(d3));//比较的是值
		System.out.println(d3.equals(d5));
		
	}
}
