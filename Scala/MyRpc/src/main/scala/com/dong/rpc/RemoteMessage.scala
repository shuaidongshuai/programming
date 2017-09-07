package com.dong.rpc

/**
  * Created by ☆东★ on 2016/12/20.
  */
trait RemoteMessage extends Serializable

//Worker -> Master 向Master发送注册消息
case class RegisterWorker(id: String, memory: Int,cores: Int) extends RemoteMessage

//Master -> Worker 注册的workerURL
case class RegisteredWorker(masterUrl: String) extends  RemoteMessage
//Worker -> self
case object SendHeartbeat
//心跳
case class Heartbeat(id: String) extends RemoteMessage
// Master -> self
case object CheckTimeOutWorker