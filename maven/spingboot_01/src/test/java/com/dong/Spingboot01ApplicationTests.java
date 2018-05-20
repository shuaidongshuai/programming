package com.dong;

import com.dong.springConfig.SpringConfigDong;
import com.dong.springConfig.User;
import com.dong.springConfig.UserService;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.test.context.junit4.SpringRunner;

import java.util.List;

@RunWith(SpringRunner.class)
@SpringBootTest
public class Spingboot01ApplicationTests {
    @Test
    public void springConfigTest() {
        // 通过Java配置来实例化Spring容器--------这里和以前是不一样的
        AnnotationConfigApplicationContext context = new AnnotationConfigApplicationContext(SpringConfigDong.class);
        UserService userService = context.getBean(UserService.class);
        List<User> users = userService.queryUserList();
        for (User user : users) {
            System.out.println(user);
        }
        // 销毁该容器
        context.close();
    }
}
