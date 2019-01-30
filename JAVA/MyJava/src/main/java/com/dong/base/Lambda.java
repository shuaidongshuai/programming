package com.dong.base;

import org.junit.Test;

public class Lambda {
    int love = 520;
    /**
     *  1 Lambda捕获局部变量是有要求的
     *      1.1 局部变量必须声明为final
     *      1.2 或者事实上是final--就是说不加final声明，但实际上这个变量没有被改变过
     *  2 为什么只对局部变量有要求？
     *      2.1 局部变量是保存在栈上的，使用Lambda的线程，可能会在分配该变量的线程将这个变量收回
     *          java在访问自由局部变量时，实际上是在访问它的副本，而不是访问原始变量
     *          如果局部变量仅仅值一次那就没有什么别了——因此就有了这个限制。
     *  3 为什么可以用Runnable接收一个Lambda？
     *      3.1 因为Runnable是一个函数接口
     */
    @Test
    public void test1(){
        String name = "东";
        Runnable r = ()     -> System.out.println("hello " + name + " " + love);
        r.run();
//        name = "Anthony"; //取消注释编译就不能通过
        love = 521; //非局部变量是可以的
    }

}
