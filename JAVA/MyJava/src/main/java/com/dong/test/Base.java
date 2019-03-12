
package com.dong.test;

import org.junit.Test;

abstract class A{
    public A(){
        list();
    }
    public void list(){
        test();
    }
    abstract void test();
}

class B extends A{
    private final static B instance = new B();
    public static B getInstance(){
        return instance;
    }
    public void test(){
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        instance.test2();
    }
    public void test2(){

    }
}

public class Base{
    @Test
    public void test() {
//        B b = B.getInstance();
//        b.test();
    }
}
