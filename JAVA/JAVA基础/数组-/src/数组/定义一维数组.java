package 数组;


public class 定义一维数组 {
	public static void main(String [] args){
		String [] student = {"张三","李四"};
		int score[] = new int[2];
		score[0]=1;
		score[1]=2;
		System.out.println(student[0]+"——同学的成绩："+score[0]);
		System.out.println(student[1]+"——同学的成绩："+score[1]);
	}
}
