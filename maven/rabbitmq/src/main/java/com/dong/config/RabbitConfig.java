package com.dong.config;

import org.springframework.amqp.core.Queue;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

/**
 * Created by ☆东★ on 2018/5/13.
 * 用来配置队列、交换器、路由等高级信息
 */
@Configuration
public class RabbitConfig {
    @Bean
    public Queue dongQueue() {
        return new Queue("dongmq"); //配置一个queue
    }

}