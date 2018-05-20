package com.dong;

import org.springframework.boot.Banner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.scheduling.annotation.EnableScheduling;

@SpringBootApplication
@EnableScheduling   //启用定时任务的配置
public class Spingboot01Application {
    public static void main(String[] args) {
//        SpringApplication.run(Spingboot01Application.class, args);
        SpringApplication application = new SpringApplication(Spingboot01Application.class);
        application.setBannerMode(Banner.Mode.OFF);
        application.run(args);
    }
}
