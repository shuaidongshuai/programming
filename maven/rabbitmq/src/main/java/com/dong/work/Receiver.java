package com.dong.work;

import org.springframework.amqp.rabbit.annotation.RabbitHandler;
import org.springframework.amqp.rabbit.annotation.RabbitListener;
import org.springframework.stereotype.Component;

/**
 * Created by ☆东★ on 2018/5/13.
 */
@Component
@RabbitListener(queues = "dongmq")  //接收 dongmq 这个 queue
public class Receiver {
    @RabbitHandler
    public void process(String data) {
        System.out.println("Receiver : " + data);
    }
}
