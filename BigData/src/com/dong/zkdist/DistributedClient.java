package com.dong.zkdist;

import java.util.ArrayList;
import java.util.List;

import org.apache.zookeeper.WatchedEvent;
import org.apache.zookeeper.Watcher;
import org.apache.zookeeper.ZooKeeper;

/*
 * 监听父节点，所以可以获得每次子节点的消息，（目的就是：让客服端可以实时监视到服务器动态）
 * 每次都获得这个父节点下的子节点，然后遍历子节点的data，就能实时刷新消息了
 */
public class DistributedClient {
	private static final String connectString = "mini1:2181";
	private static final int sessionTimeout = 2000;
	private static final String parentNode = "/servers";
	static ZooKeeper zk = null;
	// 注意:加volatile的意义何在？
		private volatile List<String> serverList;
	/**
	 * 创建到zk的客户端连接
	 */
	public void getConnect() throws Exception {
		zk = new ZooKeeper(connectString, sessionTimeout, new Watcher() {
			@Override
			public void process(WatchedEvent event) {
				// 收到事件通知后的回调函数（应该是我们自己的事件处理逻辑）
				try {
					//重新更新服务器列表，并且注册了监听
					getServerList();
				} catch (Exception e) {
				}
			}
		});
	}
	/**
	 * 获取服务器信息列表，每次有变化了，就会回调这个函数
	 */
	public void getServerList() throws Exception {
		// 获取服务器子节点信息，并且对父节点进行监听
		List<String> children = zk.getChildren(parentNode, true);
		// 先创建一个局部的list来存服务器信息
		List<String> servers = new ArrayList<String>();
		for (String child : children) {
			// child只是子节点的节点名
			byte[] data = zk.getData(parentNode + "/" + child, false, null);
			servers.add(new String(data));
		}
		// 把servers赋值给成员变量serverList，已提供给各业务线程使用
		serverList = servers;
		//打印服务器列表
		System.out.println(serverList);
	}
	/**
	 * 业务功能
	 */
	public void handleBussiness() throws InterruptedException {
		System.out.println("client start working.....");
		Thread.sleep(Long.MAX_VALUE);
	}
	public static void main(String[] args) throws Exception {
		// 获取zk连接
		DistributedClient client = new DistributedClient();
		client.getConnect();
		// 获取servers的子节点信息（并监听），从中获取服务器信息列表
		client.getServerList();
		// 业务线程启动
		client.handleBussiness();
		
	}
}
