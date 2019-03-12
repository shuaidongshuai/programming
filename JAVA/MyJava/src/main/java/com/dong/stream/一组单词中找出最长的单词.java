package com.dong.stream;

import org.junit.Test;

import java.util.Comparator;
import java.util.Optional;
import java.util.stream.Stream;

/**
 * @author com.dong
 */
public class 一组单词中找出最长的单词 {

    /**
     * reduce()擅长的是生成一个值，如果想要从Stream生成一个集合或者Map等复杂的对象该怎么办呢？终极武器collect()
     */
    @Test
    public void test() {
        Stream<String> stream = Stream.of("I", "love", "you", "too");
        Optional<String> reduce = stream.reduce((s1, s2) -> s1.length() >= s2.length() ? s1 : s2);
        System.out.println(reduce.get());
    }

    /**
     * 求单词长度和
     */
    @Test
    public void test3() {
        Stream<String> stream = Stream.of("I", "love", "you", "too");
        //1.初始值 2.累加器 3.多个部分如何合并
        Integer lengthSum = stream.reduce(0, (sum, str) -> {
            System.out.println("sum=" + sum + "  str=" + str);
            return sum + str.length();
        }, (a, b) -> {
            System.out.println("a=" + a + "  b=" + b);
            return a + b;
        });
        System.out.println(lengthSum);

        Stream<String> stream2 = Stream.of("I", "love", "you", "too");
        //1.初始值 2.累加器 3.多个部分如何合并
        Optional<String> reduce = stream2.reduce((a, b) -> {
            System.out.println("a=" + a + "  b=" + b);
            return a + b;
        });
        System.out.println(reduce.get());
    }

    @Test
    public void test4() {
        Stream<String> stream = Stream.of("I", "love", "you", "too", "");
        Optional<String> max = stream.max(Comparator.comparing(s -> s.length()));
        System.out.println(max.get());

        Stream<String> stream2 = Stream.of();
        Optional<String> min = stream2.min(Comparator.comparing(s -> s.length()));
        System.out.println(min.get());
    }

}
