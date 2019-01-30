package com.dong.dongblog;

import org.mybatis.spring.annotation.MapperScan;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
@MapperScan("com.dong.dongblog.dao")
public class DongblogApplication {

    public static void main(String[] args) {
        SpringApplication.run(DongblogApplication.class, args);
    }
}

