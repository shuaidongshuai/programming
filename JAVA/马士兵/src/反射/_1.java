package 反射;
import java.lang.reflect.*;

public class _1 {
	public static void main1(String[] args) throws Exception{
		Class c = Class.forName("反射.Person");
		Method[] me = c.getMethods();
		for(Method m : me){
			if(m.getName().equals("d2")){
				Class returnType = m.getReturnType();//获取返回值
				System.out.println("d1返回值"+returnType.getName());
			}
			if(m.getName().equals("d1")){//判断方法是否名为d1
				for(Class paramType : m.getParameterTypes())//获取参数名称
					System.out.println("d1参数："+paramType.getName());
				//调用这个方法
				Object o = c.newInstance();//调用了空参构造参数
				m.invoke(o, 12,"dong");
			}
		}
	}
	public static void main2(String[] args) throws Exception {
		Class c = Class.forName("反射.Person");
		//必须是共有的构造函数
		Constructor cs = c.getConstructor(int.class);//调用了有参的构造参数
		Person d = (Person)cs.newInstance(9);//获取对象，也就是类的实例化
		d.d2();//调用类的方法
		
		//下面是私有构造函数
		cs = c.getDeclaredConstructor(String.class);
		cs.setAccessible(true);//值为 true 则指示反射的对象在使用时应该取消 Java 语言访问检查
		Person p = (Person) cs.newInstance("hello dong");
		p.d1(11002, "dong");
	}
	public static void main3(String[] args) throws Exception {
		//反射调用非数组方法
		Class c = Class.forName("反射.Person");
		Method[] me = c.getMethods();//获取所有方法
		for(Method m : me){
			System.out.println(m.getName());
		}
		
		Method method = c.getMethod("d1", int.class,String.class);//获取方法  d1
		Object o = c.newInstance();
		method.invoke(o,1234,"hello");
		
		//调用数组方法  如main方法
		Method main = c.getMethod("main", String[].class);
//		main.invoke(o, new String[]{"aa","bb","cc"});//这样做不行，JDK会把字符串数组分开作为3个参数，但main方法只有一个参数
		main.invoke(o, (Object)new String[]{"aa","bb","cc"});//用强制类型转化  欺骗java 使java不把里面的几个字符串分开，当做一个参数 
		main.invoke(o, new Object[]{new String[]{"aa","bb","cc"}});//这样就不存在欺骗了，实实在在的传一个字符串数组进去
	}
	public static void main(String[] args) throws Exception {
		Class c = Class.forName("反射.Person");
		Object obj = c.newInstance();
		Field f = c.getField("i");
		//获取共有字段
		Object o = f.get(obj);
		//获取字段类型
		Class type = f.getType();
		if(type.equals(int.class)){
			int i = (int)o;
			System.out.println("i = "+i);
		}
		
		//获取私有  字段
		Field f2 = c.getDeclaredField("s");
		f2.setAccessible(true);
		System.out.println("i = "+f.get(obj));
	}
}
