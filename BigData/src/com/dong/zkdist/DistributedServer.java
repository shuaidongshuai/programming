package com.dong.zkdist;

import java.io.IOException;

import org.apache.zookeeper.CreateMode;
import org.apache.zookeeper.KeeperException;
import org.apache.zookeeper.WatchedEvent;
import org.apache.zookeeper.Watcher;
import org.apache.zookeeper.ZooDefs.Ids;
import org.apache.zookeeper.ZooKeeper;
import org.junit.Before;

public class DistributedServer {
	private static final String connectString = "mini1:2181";
	private static final int sessionTimeout = 2000;
	private static final String parentNode = "/servers";
	static ZooKeeper zk = null;
	/*
	 * 用于初始化ZooKeeper，并设置监听器
	 */
	public void getConnect() throws IOException{
		zk = new ZooKeeper(connectString,sessionTimeout,new Watcher(){
			@Override
			public void process(WatchedEvent event) {
				// 每次节点被增加，删除，都会执行这个回调函数，   但是改这个节点的data是不会触发的
				System.out.println(event.getType() + "---" + event.getPath());
				try {
					zk.getChildren("/", true);
				} catch (Exception e) {
				}
			}
		});
	}
	/*
	 * 向zk集群注册服务器信息
	 */
	public void registerServer(String hostname) throws KeeperException, InterruptedException {
		String create = zk.create(parentNode+"/server", hostname.getBytes(), Ids.OPEN_ACL_UNSAFE, CreateMode.EPHEMERAL_SEQUENTIAL);
		System.out.println(hostname+"is online.."+create);
	}
	/**
	 * 业务功能
	 */
	public void handleBussiness(String hostname) throws InterruptedException {
		System.out.println(hostname + "start working.....");
		Thread.sleep(Long.MAX_VALUE);
	}
	public static void main(String[] args) throws IOException, KeeperException, InterruptedException {
		//获取连接（初始化zk，并监听嘛）
		DistributedServer server = new DistributedServer();
		server.getConnect();
		
		// 利用zk连接注册服务器信息（就是创建一个节点嘛）
		server.registerServer(args[0]);
		
		// 启动业务功能(这里就是sleep而已)
		server.handleBussiness(args[0]);
	}
}
