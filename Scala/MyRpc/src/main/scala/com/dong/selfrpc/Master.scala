package com.dong.selfrpc

import akka.actor.{Actor, ActorSystem, Props}
import com.typesafe.config.ConfigFactory
import scala.concurrent.duration._

import scala.collection.mutable

/**
  * Created by ☆东★ on 2016/12/21.
  */
class MasterDong(val host: String, val port: String) extends Actor {
  val RegisterWorkers = new mutable.HashMap[String, WorkerInfo9527]
  var workerIds = new mutable.HashSet[WorkerInfo9527]()

  override def preStart(): Unit = {
    println("开启心跳检查")
    import context.dispatcher
    context.system.scheduler.schedule(0 seconds, 6 seconds, self, CheckHeart)
  }

  override def receive: Receive = {
    case RegisterWorker(workerId, memory, cores) => {
      if (!RegisterWorkers.contains(workerId)) {
        RegisterWorkers(workerId) = new WorkerInfo9527(workerId, memory, cores)
        sender ! RegDone(s"akka.tcp://MasterSystem@$host:$port/user/Master")
        println("发送：" + s"akka.tcp://MasterSystem@$host:$port/user/Master")
      }
    }
    case WorkerSendHeart(workerId) => {
      if (RegisterWorkers.contains(workerId)) {
        RegisterWorkers(workerId).lastHeartTime = System.currentTimeMillis()
      }
    }
    case CheckHeart => {
      for (i <- RegisterWorkers.keys) {
        if (System.currentTimeMillis() - RegisterWorkers(i).lastHeartTime > 6000) {
          RegisterWorkers -= i
        }
      }
      println(RegisterWorkers.size)
      //下面这样做也可以，获取断开连接的workerID集合
      //var workerInfos = RegisterWorkers.keySet.toArray.filter(System.currentTimeMillis() - RegisterWorkers(_).lastHeartTime > 6)
    }
    case "testMyself" => {
      println("自己正在测试自己")
      println("Master已经启动")
    }
  }
}

object MasterDong {
  def main(args: Array[String]): Unit = {
    val host = args(0)
    val port = args(1)
    val configStr =
      s"""
         |akka.actor.provider = "akka.remote.RemoteActorRefProvider"
         |akka.remote.netty.tcp.hostname = "$host"
         |akka.remote.netty.tcp.port = "$port"
       """.stripMargin
    val config = ConfigFactory.parseString(configStr)
    val actorSystem = ActorSystem("MasterSystem", config)
    val master = actorSystem.actorOf(Props(new MasterDong(host, port)), "MasterDong")
    master ! "testMyself"
    actorSystem.awaitTermination()
  }
}