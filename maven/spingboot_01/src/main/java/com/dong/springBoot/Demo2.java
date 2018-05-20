package com.dong.springBoot;

import com.alibaba.fastjson.JSON;
import com.dong.domain.User;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.servlet.http.HttpServletResponse;
import java.io.PrintWriter;

/**
 * Created by ☆东★ on 2018/5/5.
 */
@RestController
public class Demo2 {
    //返回json格式数据
    @RequestMapping("returnJson")
    public User returnJson(){
        User user = new User();
        user.setId(1);
        user.setName("dong dong");
        return user;
    }
    //使用 fastJson
    @RequestMapping("fastJson")
    public void fastJson(HttpServletResponse response){
        User user = new User();
        user.setId(1);
        user.setName("帅东");
        String data = JSON.toJSONString(user);
        try {
            response.setContentType("text/html;charset=UTF-8");
            PrintWriter out = response.getWriter();
            out.println(data);
            out.flush();
            out.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
