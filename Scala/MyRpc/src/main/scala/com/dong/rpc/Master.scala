package com.dong.rpc

import akka.actor.{Actor, ActorSystem, Props}
import com.typesafe.config.ConfigFactory
import scala.concurrent.duration._
import scala.collection.mutable


/**
  * Created by ☆东★ on 2016/12/18.
  */
class Master(val host: String, val port: Int) extends Actor{
  // workerId -> WorkerInfo
  val idToWorker = new mutable.HashMap[String, WorkerInfo]()    //用于查询是否包含某个ID  也存储了这个worker的info
  // WorkerInfo
  val workers = new mutable.HashSet[WorkerInfo]() //专门存workerinfo的
  //超时检查的间隔
  val CHECK_INTERVAL = 15000//15s

  override def preStart(): Unit = {
    println("Master preStart")
    //导入隐式转换
    import context.dispatcher//使用timer太low了, 可以使用akka的, 使用定时器, 要导入这个包
    //自己启动了定时器给自己发送消息，作用：处理断开连接的worker
    context.system.scheduler.schedule(0 millis,CHECK_INTERVAL millis,self,CheckTimeOutWorker)
  }

  //用于接收
  override def receive: Receive = {
    //接收worker发送过来的注册消息
    case RegisterWorker(id, memory, cores) =>{
      //判断一下，是不是已经注册过
      if(!idToWorker.contains(id)){
        //把Worker的信息封装起来保存到内存当中
        val workerInfo =  new WorkerInfo(id,memory,cores)
        idToWorker(id) = workerInfo       //把worker  id 当键值 info当值保持
        workers += workerInfo
        sender ! RegisteredWorker(s"akka.tcp://MasterSystem@$host:$port/user/Master")//通知worker注册
      }
    }
    //每次worker发送心跳过来，master就更新这个worker的时间，如果超过一定时间worker还没发送心跳，就说明断了
    case Heartbeat(id) => {
      if(idToWorker.contains(id)){
        val workerInfo = idToWorker(id)
        //既然发送过来了，就更新他的时间
        val currentTime = System.currentTimeMillis()
        workerInfo.lastHeartbeatTime = currentTime
      }
    }
    case CheckTimeOutWorker => {
      val currentTime = System.currentTimeMillis()
      //遍历所有已经注册过的worker，求：最后更新时间和现在的时间差大于CHECK_INTERVAL的set集合
      val toRemove = workers.filter(x => currentTime - x.lastHeartbeatTime > CHECK_INTERVAL)//filter是过滤，接收一个返回值为boolean的函数
      //遍历这个超时的set集合，要从workers 和 idToWorker 中删除
      for(w <- toRemove) {
        workers -= w
        idToWorker -= w.id
      }
      println(workers.size)
    }
  }
}
object Master {
  def main(args: Array[String]): Unit = {
    val host = args(0)
    val port = args(1).toInt
    // 准备配置
    val configStr =
      s"""
         |akka.actor.provider = "akka.remote.RemoteActorRefProvider"
         |akka.remote.netty.tcp.hostname = "$host"
         |akka.remote.netty.tcp.port = "$port"
       """.stripMargin
    val config = ConfigFactory.parseString(configStr)
    //ActorSystem老大，辅助创建和监控下面的Actor，他是单例
    val actorSys = ActorSystem("MasterSystem",config)
    //创建Actor, 起个名字
    val master = actorSys.actorOf(Props(new Master(host, port)),"Master00")//Master主构造器会执行
    master ! "hello"//发送消息  自己测试一下自己
    //让进程等待着, 先别结束
    actorSys.awaitTermination()
  }
}