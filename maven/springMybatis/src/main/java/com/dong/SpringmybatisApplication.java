package com.dong;

import org.mybatis.spring.annotation.MapperScan;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.web.servlet.ServletComponentScan;

@SpringBootApplication
@ServletComponentScan
@MapperScan("com.dong.dao")
public class SpringmybatisApplication {
	public static void main(String[] args) {
		SpringApplication.run(SpringmybatisApplication.class, args);
	}
}
