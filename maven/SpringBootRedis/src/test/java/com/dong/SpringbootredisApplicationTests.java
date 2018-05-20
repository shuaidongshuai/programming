package com.dong;

import com.dong.domain.User;
import org.junit.Assert;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.data.redis.core.StringRedisTemplate;
import org.springframework.data.redis.core.ValueOperations;
import org.springframework.test.context.junit4.SpringRunner;

@RunWith(SpringRunner.class)
@SpringBootTest
public class SpringbootredisApplicationTests {
	@Autowired
	private StringRedisTemplate stringRedisTemplate;
    @Autowired
    private RedisTemplate<String, User> redisTemplate;

    // 保存字符串
	@Test
	public void contextLoads() {
		stringRedisTemplate.opsForValue().set("dong", "hello");
		Assert.assertEquals("hello", stringRedisTemplate.opsForValue().get("dong"));
	}
    //存储对象---有问题-没解决
    @Test
    public void testObject() throws Exception {
        ValueOperations<String, User> operations = redisTemplate.opsForValue();
        // 保存对象
        User user = new User("超人", 20);
        operations.set(user.getUsername(), user);

        user = new User("蝙蝠侠", 30);
        operations.set(user.getUsername(), user);

        user = new User("蜘蛛侠", 40);
        operations.set(user.getUsername(), user);

        Assert.assertEquals(20, operations.get("超人").getAge().longValue());
        Assert.assertEquals(30, operations.get("蝙蝠侠").getAge().longValue());
        Assert.assertEquals(40, operations.get("蜘蛛侠").getAge().longValue());


    }
}
