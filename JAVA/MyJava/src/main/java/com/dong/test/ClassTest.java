package com.dong.test;

/**
 * @author com.dong
 */
public class ClassTest {

    public void test(Object obj, Runnable runnable, ClassTest f) {
        runnable.run();
    }

    public static void main(String[] args) {
        ClassTest classTest = new ClassTest();
        classTest.test(new Object(), new Runnable(){
            @Override
            public void run() {
                System.out.println("hello com.dong");
            }
        }, new ClassTest());
    }
}