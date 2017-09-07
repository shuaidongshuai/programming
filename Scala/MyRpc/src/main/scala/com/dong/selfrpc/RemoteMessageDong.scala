package com.dong.selfrpc

/**
  * Created by ☆东★ on 2016/12/21.
  */
trait RemoteMessageDong extends Serializable

case class RegisterWorker(WorkerId: String, val memory: Int, val cores: Int) extends  RemoteMessageDong
case class RegDone(MasterId: String) extends  RemoteMessageDong
case class StartHeart() extends RemoteMessageDong
case class WorkerSendHeart(workerId: String) extends RemoteMessageDong
case class CheckHeart() extends RemoteMessageDong