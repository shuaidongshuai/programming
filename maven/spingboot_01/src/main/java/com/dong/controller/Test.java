package com.dong.controller;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

/**
 * Created by ☆东★ on 2018/5/3.
 */
@RestController
public class Test {
    @Value(value = "${book.author}")
    private String name;

    @RequestMapping("test")
    public String test(){
        return name;
    }
}
