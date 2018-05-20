package com.dong;

import com.dong.work.Sender;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

@RunWith(SpringRunner.class)
@SpringBootTest(classes = RabbitmqApplication.class)
public class RabbitmqApplicationTests {
	@Autowired
	private Sender sender;

	@Test
	public void testRabbitmq() throws Exception {
		sender.send();
	}

}
