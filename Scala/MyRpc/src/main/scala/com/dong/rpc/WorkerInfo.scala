package com.dong.rpc

/**
  * Created by ☆东★ on 2016/12/20.
  */
class WorkerInfo(val id: String, val memory: Int, val cores: Int) {
  //TODO 上一次心跳
  var lastHeartbeatTime : Long = _
}
