package com.dong.guava;

import com.google.common.base.Optional;
import org.junit.Test;

/**
 *  Optional对象，用于不存在值表示null
 * @author dong
 */
public class OptionalTest {

    /**
     * sum() 不采取任何的保护传递的参数为null
     * @param a
     * @param b
     * @return
     */
    public Integer sum(Integer a, Integer b) {
        return a + b;
    }

    public Integer sum(Optional<Integer> a, Optional<Integer> b) {
        return a.get() + b.get();
    }

    public Integer sum2(Optional<Integer> a, Optional<Integer> b){
        //Optional.isPresent - checks the value is present or not
        System.out.println("First parameter is present: " + a.isPresent());
        System.out.println("Second parameter is present: " + b.isPresent());

        //Optional.or - returns the value if present otherwise returns
        //the default value passed.
        Integer value1 = a.or(new Integer(0));

        //Optional.get - gets the value, value should be present
        Integer value2 = b.get();

        return value1 + value2;
    }

    @Test
    public void test1() {
        Integer a =  null;
        Integer b =  new Integer(10);
        System.out.println(sum(a,b));
    }

    /**
     * Optional.of - 返回要用作参数Optional类的实例。检查传递的值是否为null。
     */
    @Test
    public void test2() {
        Integer invalidInput = null;
        Optional<Integer> a = Optional.of(invalidInput);
        Optional<Integer> b = Optional.of(new Integer(10));
        System.out.println(sum(a, b));
    }

    @Test
    public void test3() {
        Integer value1 =  null;
        Integer value2 =  new Integer(10);
        //Optional.fromNullable - allows passed parameter to be null.
        Optional<Integer> a = Optional.fromNullable(value1);
        //Optional.of - throws NullPointerException if passed parameter is null
        Optional<Integer> b = Optional.of(value2);

        System.out.println(sum2(a,b));
    }

}
