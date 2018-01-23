class Professor implements Cloneable     
{    
     String name;    
     int age;    
     Professor(String name,int age)    
     {    
        this.name=name;    
        this.age=age;    
     }
	protected Object clone() throws CloneNotSupportedException {
		return super.clone();
	}    
}    
class Student implements Cloneable    
{    
     String name;// 常量对象。    
     int age;    
     Professor p;// 学生1和学生2的引用值都是一样的。    
     Student(String name,int age,Professor p)    
     {    
        this.name=name;    
        this.age=age;    
        this.p=p;    
     }    
    public Object clone()    
     {    
         Student o=null;    
        try    
         {    
             o=(Student)super.clone();    
//           o.p=(Professor)p.clone();//加上这句话就是深拷贝，没有这句话就是浅拷贝
         }    
        catch(CloneNotSupportedException e)    
         {    
             System.out.println(e.toString());    
         }    
        return o;    
     }
}    
public class PriNum {
	public static void main(String[] args) throws CloneNotSupportedException {
		Professor p=new Professor("wangwu",50);    
	       Student s1=new Student("zhangsan",18,p);    
	       Student s2=(Student)s1.clone();    
	       s2.p.name="lisi";    
	       System.out.println("name="+s1.p.name);
	       /*加上：name=wangwu  没加：name=lisi */
	}
}
