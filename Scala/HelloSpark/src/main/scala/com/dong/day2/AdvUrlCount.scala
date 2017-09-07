package com.dong.day2

import java.net.URL

import org.apache.spark.{SparkConf, SparkContext}

/**
  * Created by ☆东★ on 2016/12/30.
  */
object AdvUrlCount {
  def main(args: Array[String]): Unit = {
    //从数据库中加载规则
    val arr = Array("java.itcast.cn", "php.itcast.cn", "net.itcast.cn")

    val conf = new SparkConf().setAppName("UrlCount").setMaster("local[2]")
    val sc = new SparkContext(conf)
    val rdd0 = sc.textFile("E:\\study_materials\\Bdata\\资料\\day29\\itcast.log").map(line => {
      val split = line.split("\t")
      (split(1), 1)
    })
    val rdd1 = rdd0.reduceByKey(_ + _)
    val rdd2 = rdd1.map(line => {
      val url = line._1
      val host = new URL(url).getHost
      (host, url, line._2)
    })
    for(ins <- arr){
      val rdd = rdd2.filter(_._1 == ins)
      val result= rdd.sortBy(_._3, false).take(3)		//rdd的排序，当数据过大会分布到其它机器上排序
      //通过JDBC向数据库中存储数据
      //id，学院，URL，次数， 访问日期
      println("++++++"+rdd.collect().toBuffer)
      println("------"+result.toBuffer)
    }
   // println(rdd1.collect().toBuffer)
  }
}
