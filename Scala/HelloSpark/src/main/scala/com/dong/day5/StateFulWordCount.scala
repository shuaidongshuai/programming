package com.dong.day5

import org.apache.spark.streaming.{Seconds, StreamingContext}
import org.apache.spark.{HashPartitioner, SparkConf, SparkContext}

/**
  * Created by ☆东★ on 2017/1/7.
  */
object StateFulWordCount {
  def main(args: Array[String]): Unit = {
    LoggerLevels.setStreamingLogLevels()
    val conf = new SparkConf().setAppName("State").setMaster("local[2]")
    val sc = new SparkContext(conf)
    val ssc = new StreamingContext(sc, Seconds(6))

    //updateStateByKey必须设置setCheckpointDir
    sc.setCheckpointDir("E:\\study_materials\\Bdata\\day32")

    val ds = ssc.socketTextStream("139.199.26.222", 9999)
    val res = ds.flatMap(_.split(" ")).map((_, 1)).updateStateByKey(updateFunc,new HashPartitioner(sc.defaultParallelism),true)//true记住partitioner
    res.print()
    ssc.start()
    ssc.awaitTermination()
  }
  
  //参数就是一个iterator  里面还有参数，String 是 key |  sql就是values  | Option就是上次的values 这个数要保存起来
  val updateFunc = (it: Iterator[(String, Seq[Int], Option[Int])]) => {
    //it.map{case(k,v,pastV) => (k,v.sum + pastV.getOrElse(0))}
    it.map(t => (t._1,t._2.sum + t._3.getOrElse(0)))
  }
}
