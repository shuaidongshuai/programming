package 接口;

interface A{
	float PI = 3.14f;
	float getArea();
}
interface B{
	float PI = 3.1415f;
	float getArea();
}
class Area implements A,B{
	private float radius;
	Area(){
		radius = 0;
	}
	Area(float r){
		radius = r;
	}
	public float getArea(){
		float area = A.PI * radius * radius;// A.PI表示用A接口的PI
		return area;
	}
}

public class 多个接口常亮方法冲突 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Area a = new Area();
		float area = a.getArea();
		System.out.println(area);
		
		a = new Area(1);
		area = a.getArea();
		System.out.println(area);
	}

}
