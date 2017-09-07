package com.dong.day5

import org.apache.spark.streaming.{Seconds, StreamingContext}
import org.apache.spark.{SparkConf, SparkContext}

/**
  * Created by ☆东★ on 2017/1/6.
  */
object StreamingWordCount {
  def main(args: Array[String]): Unit = {
    LoggerLevels.setStreamingLogLevels()
    val conf = new SparkConf().setAppName("Streaming").setMaster("local[2]")
    val sc = new SparkContext(conf)
    val ssc = new StreamingContext(sc,Seconds(5))//5s刷一次

    //构建一个DStream
    val ds = ssc.socketTextStream("139.199.26.222",9999)
    //DStream是一个特殊的RDD
    val res = ds.flatMap(_.split(" ")).map((_,1)).reduceByKey(_+_)
    //打印
    res.print()

    //启动Ds
    ssc.start()
    //等待结束
    ssc.awaitTermination()
  }
}
