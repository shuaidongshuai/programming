package com.dong.jmap;

import java.util.ArrayList;
import java.util.List;

class A{
    private int a;
}

class B{
    private A a;
}

public class OOM {

    public static void main(String[] args) {
        List<B> bList = new ArrayList<>();
        while(true){
            bList.add(new B());
        }
    }
}
