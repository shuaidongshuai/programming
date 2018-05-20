package com.dong.springBoot;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

@SpringBootApplication
@Controller
public class Demo1 {
    @RequestMapping("demo1")
    @ResponseBody   //把返回的数据写到ResponseBody中  Controller + ResponseBody = RestController
    public String hello(){
        return "hello dong dong! 帅东";
    }
    public static void main(String[] args) {
        SpringApplication.run(Demo1.class, args);
    }
}
