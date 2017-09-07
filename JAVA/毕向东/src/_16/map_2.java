package _16;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

/*
 * map取出方式（两种）
 * 1，keySet：将map中所有的键值存入到Set集合，因为Set具备迭代器，所以可以迭代方式取出所有的键，
 * 			    再根据get方法。获取每一个键对应的值
 * 
 * 			Map集合的取出原理，将map集合转成set集合，再通过set集合中的迭代器取出
 * 2，Set<Map.Entry<k,v>> entrySet：将map集合中的映射关系存入到了Set集合中，而这个关系的数据类型就是Map.Entry
 * 2，
 */
public class map_2 {
	public static void main(String[] args) {
		Map<String,String> map = new HashMap<String,String>();
		map.put("02","zhangsan2");
		map.put("03","zhangsan2");
		map.put("01","zhangsan1");
		System.out.println(map);
		//先获取map集合中的所有键的Set集合
		Set<String> keyset = map.keySet();//键值的String泛型就是String
		//有了Set集合，就可以获取其迭代器
		for(Iterator<String> it = keyset.iterator();it.hasNext();){
			String key = it.next();
			String value = map.get(key);
			System.out.println(value);
		}
	}
	public static void main2(String[] args) {
		Map<String,String> map = new HashMap<String,String>();
		map.put("02","zhangsan2");
		map.put("03","zhangsan3");
		map.put("01","zhangsan1");
		//将map集合中的映射关系取出。存入Set集合
		Set<Map.Entry<String,String>> entryset = map.entrySet();
		
		for(Iterator<Map.Entry<String,String>> it = entryset.iterator();it.hasNext();){
			Map.Entry<String,String> me = it.next();
			String key = me.getKey();
			String value = me.getValue();
			System.out.println(key+"         "+value);
		}
		
	}
}
