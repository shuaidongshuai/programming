package com.dong.base;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.FutureTask;

/**
 * @author com.dong
 */

class Worker {
    public String name;
    Worker(String name) {
        this.name = name;
    }
}

/**
 * @author com.dong
 */
public class FutureTaskTest {
    public static FutureTask<Worker> addWorker(String name) {
        FutureTask<Worker> futureTask = new FutureTask<>(() -> {
            System.out.println(name + " do something");
            Thread.sleep(1000);
            return new Worker(name);
        });
        new Thread(futureTask).start();
        return futureTask;
    }

    public static void main(String[] args) throws ExecutionException, InterruptedException {
        long start = System.currentTimeMillis();
        List<FutureTask<Worker>> listTask = new ArrayList<>();
        listTask.add(addWorker("东1"));
        listTask.add(addWorker("东2"));
        listTask.add(addWorker("东3"));
        for(FutureTask<Worker> futureTask : listTask){
            Worker worker = futureTask.get();
            System.out.println("返回值：" + worker.name);
        }
        long end = System.currentTimeMillis();
        System.out.println("耗时：" + (end - start));
    }
}
