package com.dong.base;

import org.junit.Test;

import java.text.Collator;
import java.util.*;

/**
 * @author dong
 */
public class 中文拼音排序 {
    private final static Comparator CHINACOMPARE = Collator.getInstance(Locale.CHINA);

    @Test
    public void sortList(){
        List<String> list = Arrays.asList("张三", "李四", "帅东", "大东");
        Collections.sort(list, CHINACOMPARE);
        for (String name : list) {
            System.out.println(name);
        }
    }

    @Test
    public void sortArray(){
       String[] arr = {"张三", "李四", "帅东", "大东"};
       Arrays.sort(arr, CHINACOMPARE);
        for (String name : arr) {
            System.out.println(name);
        }
    }
}
