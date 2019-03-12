package com.dong.stream;

import org.junit.Test;

public class 找出字符串中小写字母个数 {
    @Test
    public void test1(){
        long count = countLowercaseLetters("helloDong");
        System.out.println(count);
    }

    public long countLowercaseLetters(String string) {
        return string.chars()
                .filter(Character::isLowerCase)
                .count();
    }
}
