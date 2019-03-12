package com.dong.stream;

import org.junit.Test;

import java.util.Arrays;
import java.util.List;

public class 累加 {

    @Test
    public void test1(){
        List<Integer> list = Arrays.asList(2, 4, 6, 8);
        System.out.println(count(list));
        System.out.println(count2(list));
    }

    /**
     * 计算个数
     * @param list
     * @return
     */
    public long count(List<Integer> list){
        return list.stream().count();
    }

    /**
     * 计算总和
     * @param list
     * @return
     */
    public long count2(List<Integer> list){
        return list.stream().reduce(0, (sum, x) -> sum + x);
    }
}
