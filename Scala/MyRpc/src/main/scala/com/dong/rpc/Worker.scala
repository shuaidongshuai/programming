package com.dong.rpc

import java.util.UUID

import akka.actor.{Actor, ActorSelection, ActorSystem, Props}
import com.typesafe.config.ConfigFactory
import scala.concurrent.duration._
/**
  * Created by ☆东★ on 2016/12/18.
  */
class Worker(val masterHost: String, val masterPort: Int, val memory: Int, val cores: Int) extends Actor {
  var actorSelection: ActorSelection = _
  //用于给Master发送消息
  val workerId = UUID.randomUUID().toString
  //产生一个随机数
  val HEART_INTERVAL = 10000 //10s时间间隔

  override def preStart(): Unit = {
    //在master启动时会打印下面的那个协议, 可以先用这个做一个标志, 连接哪个master
    //继承actor后会有一个context, 可以通过它来连接
    actorSelection = context.actorSelection(s"akka.tcp://MasterSystem@$masterHost:$masterPort/user/Master00") //需要有/user, Master要和master那边创建的名字保持一致
    //向Master发送注册消息
    actorSelection ! RegisterWorker(workerId, memory, cores)
  }

  override def receive: Receive = {
    case RegisteredWorker(masterUrl) => {
      //启动定时器发送心跳
      import context.dispatcher
      //多长时间后执行 单位,多长时间执行一次 单位
      // 消息的接受者(直接给master发不好, 先给自己发送消息,以后可以做下判断, 什么情况下再发送消息), 信息
      context.system.scheduler.schedule(0 millis, HEART_INTERVAL millis, self, SendHeartbeat)
    }
    case SendHeartbeat => {
      println("send heartbeat to master")
      actorSelection ! Heartbeat(workerId)
    }
  }
}

object Worker {
  def main(args: Array[String]): Unit = {
    val host = args(0)
    val port = args(1).toInt
    val masterHost = args(2)
    val masterPort = args(3).toInt
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
    val master = actorSys.actorOf(Props(new Worker(masterHost, masterPort, memory, cores)), "Worker1")
    actorSys.awaitTermination()
  }
}
