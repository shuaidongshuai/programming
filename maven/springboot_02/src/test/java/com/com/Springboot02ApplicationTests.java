package com.com;

import com.dong.Demo.AsyncTask;
import com.dong.Demo.AsyncTask2;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.scheduling.annotation.EnableAsync;
import org.springframework.test.context.junit4.SpringRunner;

import java.util.concurrent.Future;

@RunWith(SpringRunner.class)
@SpringBootTest(classes = {AsyncTask.class, AsyncTask2.class})
@EnableAsync
public class Springboot02ApplicationTests {
	@Autowired
    private AsyncTask asyncTask;
    @Autowired
    private AsyncTask2 asyncTask2;
	@Test
	public void asyncTaskTest() throws Exception {
		asyncTask2.doTaskOne();
		asyncTask2.doTaskTwo();
		asyncTask2.doTaskThree();
        Thread.sleep(10000);
	}
    @Test
    public void asyncTaskTest2() throws Exception {
        long start = System.currentTimeMillis();
        Future<String> task1 = asyncTask2.doTaskOne();
        Future<String> task2 = asyncTask2.doTaskTwo();
        Future<String> task3 = asyncTask2.doTaskThree();
        while(true) {
            if(task1.isDone() && task2.isDone() && task3.isDone()) {
                // 三个任务都调用完成，退出循环等待
                break;
            }
            Thread.sleep(1000);
        }
        long end = System.currentTimeMillis();
        System.out.println("任务全部完成，总耗时：" + (end - start) + "毫秒");
    }

}
