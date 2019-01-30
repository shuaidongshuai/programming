package com.dong.test;

import org.junit.Test;

import java.util.HashMap;
import java.util.Map;

/**
 * @author dong
 */
public class HashMapTest {
    @Test
    public void test(){
        MyString myString1 = new MyString("dong");
        MyString myString2 = new MyString("dong");
        MyString myString3 = new MyString("dong");
        Map<MyString, Integer> map = new HashMap<>();
        map.put(myString1, 1);
        map.put(myString2, 2);
        map.put(myString3, 3);

        for(Map.Entry<MyString, Integer> m : map.entrySet()){
            System.out.println("key:" + m.getKey().str + "\tval:" + m.getValue());
        }

        System.out.println(map.get(new MyString("dong")));
    }
    class MyString{
        String str;

        MyString(String str){
            this.str = str;
        }

        @Override
        public boolean equals(Object obj) {
            if(obj == this){
                return true;
            } else if(obj == null){
                return false;
            }
            MyString myString = (MyString)obj;
            return str.equals(myString.str);
        }
    }
}
