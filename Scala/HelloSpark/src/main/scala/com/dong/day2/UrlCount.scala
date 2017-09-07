package com.dong.day2

import java.net.URL

import org.apache.spark.{SparkConf, SparkContext}

/**
  * Created by ☆东★ on 2016/12/30.
  */
object UrlCount {
  def main(args: Array[String]): Unit = {
    val conf = new SparkConf().setAppName("UrlCount").setMaster("local[2]")
    val sc = new SparkContext(conf)
    val rdd0 = sc.textFile("E:\\study_materials\\Bdata\\资料\\day29\\itcast.log").map(line => {
      val split = line.split("\t")
      (split(1), 1)
    })
    val rdd1 = rdd0.reduceByKey(_ + _)
    //(http://php.itcast.cn/php/course.shtml,459)
    val rdd2 = rdd1.map(line => {
      val url = line._1
      val host = new URL(url).getHost
      (host, url, line._2)
    })
    val rdd3 = rdd2.groupBy(_._1)
    //(net.itcast.cn,
    // CompactBuffer((net.itcast.cn,http://net.itcast.cn/net/video.shtml,521),
    // (net.itcast.cn,http://net.itcast.cn/net/course.shtml,521),
    // (net.itcast.cn,http://net.itcast.cn/net/teacher.shtml,512))),
    val rdd4 = rdd3.mapValues(it => {
      //(net.itcast.cn,()), (java.itcast.cn,()), (php.itcast.cn,())
      it.toList.sortBy(_._3)//.reverse.take(3)  //用的是java的集合，只能在内存中完成，有可能内存会溢出
    })
    // (net.itcast.cn,List(
    // (net.itcast.cn,http://net.itcast.cn/net/teacher.shtml,512),
    // (net.itcast.cn,http://net.itcast.cn/net/video.shtml,521),
    // (net.itcast.cn,http://net.itcast.cn/net/course.shtml,521))),
    println(rdd4.collect().toBuffer)
    sc.stop()
  }
}
