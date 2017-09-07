package com.dong.zookeeper;

import java.io.IOException;
import java.util.List;

import org.apache.zookeeper.CreateMode;
import org.apache.zookeeper.KeeperException;
import org.apache.zookeeper.WatchedEvent;
import org.apache.zookeeper.Watcher;
import org.apache.zookeeper.ZooDefs.Ids;
import org.apache.zookeeper.ZooKeeper;
import org.apache.zookeeper.data.Stat;
import org.junit.Before;
import org.junit.Test;
/*
 * 2、如果Run as --->Junit Test，运行含有@Test注释的方法是，那么所有注解方法都将被执行，所含的执行顺序是：
     @BeforeClass ，@Before，@Test，@After，@AfterClass
 * */
public class Zk {
	/*
	 * 2181（客服端端口）在/zookeeper-3.4.5/conf/zoo.cfg中可以修改
	 * 要用mini1这个名字，需要在C:\windows\system32\drivers\etc\hosts 里面改
	 * 发现不能用"mini1:2181,mini2:2181,mini3:2181";这样连着用，我反正是连接不上，我只能连接一个
	 */
	//private static final String connectString = "mini1:2181,mini2:2181,mini3:2181";
	private static final String connectString = "mini1:2181";
	private static final int sessionTimeout = 2000;
	static ZooKeeper zkClient = null;
	@Before
	public void init() throws IOException{
		zkClient = new ZooKeeper(connectString,sessionTimeout,new Watcher(){
			@Override
			public void process(WatchedEvent event) {
				// 每次节点被增加，删除，都会执行这个回调函数，   但是改这个节点的data是不会触发的
				System.out.println(event.getType() + "---" + event.getPath());
				try {
					zkClient.getChildren("/", true);
				} catch (Exception e) {
				}
			}
		});
	}
	// 创建数据节点到zk中
	@Test
	public void Create() throws KeeperException, InterruptedException{
		// 参数1：要创建的节点的路径 参数2：节点大数据 参数3：节点的权限 参数4：节点的类型
		//上传的数据可以是任何类型，但都要转成byte[]
		String nodeCreate = zkClient.create("/eclipse", "hello_zk".getBytes(),  Ids.OPEN_ACL_UNSAFE, CreateMode.PERSISTENT);
	}
	//判断znode是否存在
	@Test	
	public void testExist() throws Exception{
		Stat stat = zkClient.exists("/eclipse", false);
		System.out.println(stat==null?"not exist":"exist");
	}
	// 获取子节点
	@Test
	public void getChildren() throws Exception {
		List<String> children = zkClient.getChildren("/", true);
		for (String child : children) {
			System.out.println(child);
		}
		Thread.sleep(Long.MAX_VALUE);
	}
	//获取znode的数据
	@Test
	public void getData() throws KeeperException, InterruptedException{
		byte[] data = zkClient.getData("/eclipse", false, null);
		System.out.println(new String(data));
	}
	//删除znode
	@Test
	public void deleteZnode() throws Exception {
		//参数2：指定要删除的版本，-1表示删除所有版本
		zkClient.delete("/eclipse", -1);
	}
	//修改znode信息
	@Test
	public void setData() throws Exception {
		zkClient.setData("/root/dong", "imissyou angelababy".getBytes(), -1);
	}
	
	
	
	
	
	
	public static void main(String[] args) throws IOException, KeeperException, InterruptedException {
		 ZooKeeper zk = new ZooKeeper("192.168.56.10:2181", 3000, null);  
	        System.out.println("=========创建节点===========");  
	        if(zk.exists("/test", false) == null)  
	        {  
	            zk.create("/test", "znode1".getBytes(), Ids.OPEN_ACL_UNSAFE, CreateMode.PERSISTENT);  //create创建节点
	        }  
	        System.out.println("=============查看节点是否安装成功===============");  
	        System.out.println(new String(zk.getData("/test", false, null)));  						//  getData查看节点数据
	          
	        System.out.println("=========修改节点的数据==========");  
	        zk.setData("/test", "zNode2".getBytes(), -1);  											//  修改节点数据
	        System.out.println("========查看修改的节点是否成功=========");  
	        System.out.println(new String(zk.getData("/test", false, null)));  
	          
	        System.out.println("=======删除节点==========");  
	        zk.delete("/test", -1);  																// delete 删除节点
	        System.out.println("==========查看节点是否被删除============");  
	        System.out.println("节点状态：" + zk.exists("/test", false));  								// 判断节点是否存在exists
	        zk.close();  
	}
}

