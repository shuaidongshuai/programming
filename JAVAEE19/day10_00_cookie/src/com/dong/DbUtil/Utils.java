package com.dong.DbUtil;

import java.util.HashMap;
import java.util.Map;

import com.dong.entity.Beauty;

//本来要连接数据库但是为了简便，就直接赋值
public class Utils {
	private static Map<String,Beauty> beauty = new HashMap<String,Beauty>();
	
	static {
		beauty.put("1", new Beauty("赵丽颖","10000"));
		beauty.put("2", new Beauty("赵奕欢","1000"));
		beauty.put("3", new Beauty("金莎","12000"));
		beauty.put("4", new Beauty("杨幂","5000"));
		beauty.put("5", new Beauty("郑爽","6000"));
	}
	
	public static Map<String,Beauty> findAllBeauty(){
		return beauty;
	}
	
	//根据键值   查找数据
	public static Beauty findBeauty(String id){
		return beauty.get(id);
	}
}
