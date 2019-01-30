package com.dong.base;

/**
 * @author com.dong
 */

class Food{}

class Fruit {}

class Apple2 extends Fruit {}

class Plate<T> {
    private T item;
    public Plate(T t) {item = t;}
    public void set(T t) {item = t;}
    public T get() {return item;}
}

public class 泛型super和extends {
    public static void main(String[] args) {
        //“装苹果的盘子”无法转换成“装水果的盘子”
        //Plate<Fruit> p = new Plate<Apple2>(new Apple2());

        //上界通配符
        Plate<? extends Fruit> p1 = new Plate<>(new Apple2());
        //p1.set(new Apple2());//不能使用set方法，因为无下界，有可能类型T是香蕉
        Fruit fruit = p1.get();//get可以

        //下界通配符
        Plate<? super Fruit> p2 = new Plate<>(new Food());
        p2.set(new Apple2());//可以set，只要是Fruit的子类都行
        Object object = p2.get();//可以get，但是返回类型都是object
    }
}
