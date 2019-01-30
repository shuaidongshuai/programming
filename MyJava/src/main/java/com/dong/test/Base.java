
package com.dong.test;

import org.junit.Test;

import java.io.IOException;
import java.util.*;

public class Base{
    @Test
    public void test() {
        Blip2 b = new Blip2();
        b.test();

        hello();

        List<String> list = new ArrayList<>();
        list.add("");

        Dog dog = new Dog();
        dog.test1();
    }
    public void hello(){
        System.out.println("hello");
    }
}

class Dog{
    public void test1(){
        test2();
    }

    private void test2() {
        test3();
    }

    private void test3() {
        Blip1 blip1 = new Blip1();
        try {
            blip1.readExternal(null);
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }
}