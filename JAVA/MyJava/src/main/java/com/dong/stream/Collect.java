package com.dong.stream;

import org.junit.Test;

import java.util.Map;
import java.util.function.Function;
import java.util.stream.Collectors;
import java.util.stream.Stream;

/**
 * @author com.dong
 */
public class Collect {
    @Test
    public void test() {
        // 将Stream转换成容器
        Stream<String> stream = Stream.of("I", "love", "you", "too");

        //List<String> list = stream.collect(Collectors.toList());

        //Set<String> set = stream.collect(Collectors.toSet());
        /**
         * String::length的语法形式叫做方法引用，这种语法用来替代某些特定形式Lambda表达式。如果Lambda表达式的全部内容就是调用一个已有的方法，那么可以用方法引用来替代Lambda表达式
         * 引用静态方法       Integer::sum
         * 引用某个对象的方法	list::add
         * 引用某个类的方法	String::length
         * 引用构造方法	    HashMap::new
         */
        Map<String, Integer> map = stream.collect(Collectors.toMap(Function.identity(), String::length));
        for(Map.Entry<String, Integer> m : map.entrySet()){
            System.out.println(m.getKey() + " " + m.getValue());
        }
    }
}
