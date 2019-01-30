package com.dong.base;

import org.junit.Test;

import java.util.concurrent.CompletableFuture;

/**
 * @author com.dong
 */
public class CompletableFutureTest {

    @Test
    public void testCompletableFuture() throws Exception {
        // case1: supplyAsync用于有返回值的任务
        CompletableFuture<String> future = CompletableFuture.supplyAsync(() -> {
            System.out.println("supplyAsync start");
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
            }
            System.out.println("supplyAsync end");
            return "Return result of Supply Async";
        });
        // case2: thenRun，与supplyAsync同线程
        future.thenRun(() -> {
            System.out.println("thenRun");
        });
        // case2: thenRunAsync，另启动线程执行
        future.thenRunAsync(() -> {
            System.out.println("thenRunAsync start");
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
            }
            System.out.println("thenRunAsync end");
        });

        // 主动触发Complete结束方法
        // future.complete("Manual complete value.");

        //whenComplete用于获取结果
        future.whenComplete((v, e) -> {
            System.out.println("WhenComplete value: " + v);
            System.out.println("WhenComplete exception: " + e);
        });

        //runAsync则用于没有返回值的任务
        CompletableFuture<Void> future2 = CompletableFuture.runAsync(() -> {
            System.out.println("runAsync start");
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
            }
            System.out.println("runAsync end");
        });

        CompletableFuture<String> future3 = CompletableFuture.supplyAsync(() -> "hello");
        CompletableFuture<String> future4 = CompletableFuture.supplyAsync(() -> "world");
        CompletableFuture<String> f = future3.thenCombine(future4, (x, y) -> x + "-" + y);
        System.out.println(f.get());
        //future2.get();
    }

}
