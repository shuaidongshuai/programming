package com.dong.selfrpc

import java.util.UUID

import akka.actor.{Actor, ActorSelection, ActorSystem, Props}
import com.typesafe.config.ConfigFactory

import scala.concurrent.duration._

/**
  * Created by ☆东★ on 2016/12/21.
  */
class Worker9527(val host: String, val port: String, val memory: Int, val cores: Int) extends Actor {
  var worker: ActorSelection = _
  var workerId = UUID.randomUUID().toString

  override def preStart(): Unit = {
    println("发送："+s"akka.tcp://MasterSystem@$host:$port/user/MasterDong")
    worker = context.actorSelection(s"akka.tcp://MasterSystem@$host:$port/user/MasterDong")
    worker ! RegisterWorker(workerId, memory, cores)
  }

  override def receive: Receive = {
    case RegDone(masterId) => {
      println("Master 已经和自己建立好了连接")
      println("启动心跳机制")
      import context.dispatcher
      context.system.scheduler.schedule(0 seconds, 5 seconds, self, StartHeart)
    }
    case StartHeart => {
      println("send heartbeat to master")
      worker ! WorkerSendHeart(workerId)
    }
  }
}
object Worker9527{
  def main(args: Array[String]): Unit = {
    val host = args(0)
    val port = args(1)
    val masterHost = args(2)
    val masterPort = args(3)
    val memory = args(4).toInt
    val cores = args(5).toInt
    // 准备配置
    val confStr =
      s"""
         |akka.actor.provider = "akka.remote.RemoteActorRefProvider"
         |akka.remote.netty.tcp.hostname = "$host"
         |akka.remote.netty.tcp.port = "$port"
       """.stripMargin
    val config = ConfigFactory.parseString(confStr)
    //ActorSystem老大，辅助创建和监控下面的Actor，他是单例
    val actorSys = ActorSystem("WorkerSystem", config)
    //创建Actor, 起个名字
    val master = actorSys.actorOf(Props(new Worker9527(masterHost, masterPort, memory, cores)), "Worker9527")
    actorSys.awaitTermination()
  }
}
