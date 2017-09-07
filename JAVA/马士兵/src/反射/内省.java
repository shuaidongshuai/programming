package 反射;

import java.beans.BeanInfo;
import java.beans.IntrospectionException;
import java.beans.Introspector;
import java.beans.PropertyDescriptor;

/*
 * static BeanInfo getBeanInfo(Class<?> beanClass) 
          在 Java Bean 上进行内省，了解其所有属性、公开的方法和事件 
          
          PropertyDescriptor[] getPropertyDescriptors() 
          获得 beans PropertyDescriptor。 
 */
public class 内省 {
	public static void main(String[] args) throws Exception {
		BeanInfo info = Introspector.getBeanInfo(Person.class,Object.class);//introspector内省
		PropertyDescriptor[] pd = info.getPropertyDescriptors();
		for(PropertyDescriptor p : pd){
			System.out.println(p.getName());
		}
		
	}
}
