package _16;

import java.util.*;
/*
 * 为什么Students不需要hashCode 和equals  方法？
 * 因为  Students 没有座位 HashMap的key（键值），，，HashMap的键值是，String，这个类 这个类中有自己的HashCode，equals方法
 */
class Students{
	private String name;
	private int id;
	
	Students(String name,int id){
		this.name = name;
		this.id  = id;
	}
	
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public int getId() {
		return id;
	}
	public void setId(int id) {
		this.id = id;
	}
	public String toString(){
		return name+"      "+id;
	}
}
public class map_5_练习 {
	public static void main(String[] args) {
		HashMap<String,List<Students>> czbk = new HashMap<String,List<Students>>();//存的是一个班
		
		List<Students> yure = new ArrayList<Students>();//存的是一个班的  学生
		List<Students> jiuye = new ArrayList<Students>();
		
		czbk.put("1yureban", yure);//把一个班放入 HashMap集合中	
		czbk.put("2jiuyeban", jiuye);
		
		yure.add(new Students("张三",01));//往一个班中放学生
		yure.add(new Students("李四",02));
		jiuye.add(new Students("王五",01));
		jiuye.add(new Students("赵六",02));
		
		for(Iterator<String> it = czbk.keySet().iterator();it.hasNext();){
			String roomNmae = it.next();//取的是自定义的班级（key）
			List<Students> room =  czbk.get(roomNmae);//取的是具体的某一个班（Value）
			
			System.out.println(roomNmae);
			
			for(Iterator<Students> it2 = room.iterator();it2.hasNext();){//在这个班级里面进行遍历，遍历每一个学生
				Students s = it2.next();
				System.out.println(s.getName()+"      "+s.getId());
			}
		}
	}
}
