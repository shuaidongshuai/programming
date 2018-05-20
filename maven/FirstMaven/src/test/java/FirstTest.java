import junit.framework.Assert;
import org.junit.Test;

/**
 * Created by ☆东★ on 2018/5/2.
 */
public class FirstTest {
    @Test
    public void test(){
        First first = new First();
        String name = first.getName();
        Assert.assertEquals("帅东", name);
    }
}