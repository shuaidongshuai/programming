package com.dong;

import lombok.extern.slf4j.Slf4j;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

/**
 * Created by ☆东★ on 2018/5/20.
 *      ERROR(ERROR_INT, "ERROR"),  最高级
 *      WARN(WARN_INT, "WARN"),
 *      INFO(INFO_INT, "INFO"),
 *      DEBUG(DEBUG_INT, "DEBUG"),
 *      TRACE(TRACE_INT, "TRACE");
 */
@RunWith(SpringRunner.class)
@SpringBootTest
@Slf4j
public class LoggerTest {
    //Demo1
    private final Logger logger = LoggerFactory.getLogger(LoggerTest.class);
    @Test
    public void Demo1(){
        logger.debug("debug........");
        logger.info("info..........");
        logger.error("error..........");
    }
    //Demo2 + @Slf2j(需要lombok依赖)
    @Test
    public void Demo2(){
        String name = "东";
        String password = "123456";

        log.debug("debug...");
        //两种加入变量的方法
        log.info("name: " + name + " ,password: " + password);
        log.info("name: {}, password: {}", name, password);
        log.warn("warn...");
        log.error("error...");
    }
}
