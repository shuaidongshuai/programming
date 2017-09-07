package 接口;

public class 接口可以多继承 {
	public static void main(String[] args) {
		F f = new F();
		f.a();
		f.b();
		f.c();
}
}
interface E{
	void a();
}
interface D{
	void b();
}

//接口可以多继承
interface C extends E,D{
	void c();
}

class F implements C{

	@Override
	public void a() {
		// TODO Auto-generated method stub
		System.out.println("this is a" );
	}

	@Override
	public void b() {
		// TODO Auto-generated method stub
		System.out.println("this is b");
	}

	@Override
	public void c() {
		// TODO Auto-generated method stub
		System.out.println("this is c ");
	}
	
}
