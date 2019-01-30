package com.dong.base;

import java.util.ArrayList;
import java.util.List;

import static java.util.stream.Collectors.toList;

class Apple{
    public String Color;
    public int weight;

    public Apple(String color, int weight) {
        Color = color;
        this.weight = weight;
    }

    @Override
    public String toString() {
        return "Apple{" +
                "Color='" + Color + '\'' +
                ", weight=" + weight +
                '}';
    }
}

interface Predicate<T>{
    public boolean choose(T t);
}

public class FilterApple {
    public static ArrayList<Apple> filter(ArrayList<Apple> apples, Predicate<Apple> p){
        ArrayList<Apple> res = new ArrayList<Apple>();
        for(Apple apple : apples){
            if(p.choose(apple)){
                res.add(apple);
            }
        }
        return res;
    }

    public static void main(String[] args) {
        ArrayList<Apple> apples = new ArrayList<Apple>();
        apples.add(new Apple("red", 10));
        apples.add(new Apple("red", 20));
        apples.add(new Apple("green", 10));
        apples.add(new Apple("green", 20));

        ArrayList<Apple> res = filter(apples, (Apple a) -> a.Color == "red");
        System.out.println("红苹果：");
        for (Apple a : res){
            System.out.println(a);
        }

        res = filter(apples, (Apple a) -> a.weight > 10);
        System.out.println("重量10以上的：");
        for (Apple a : res){
            System.out.println(a);
        }
        List<Apple> appleList = apples.stream().filter((Apple a) -> a.weight > 10).collect(toList());
        System.out.println("利用JAVA6 Stream API：");
        for (Apple a : appleList){
            System.out.println(a);
        }
    }
}
