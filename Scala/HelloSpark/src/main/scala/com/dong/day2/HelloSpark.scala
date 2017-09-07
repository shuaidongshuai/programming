package com.dong.day2

import org.apache.spark.{SparkConf, SparkContext}

/**
  * Created by ☆东★ on 2016/12/23.
  */
object HelloSpark {
  def main(args: Array[String]): Unit = {
    //非常重要，是通向Spark集群的入口
    val conf = new SparkConf().setAppName("WC").setMaster("local")
    val sc = new SparkContext(conf)
    //sc.textFile("C:\\Users\\37916\\Desktop\\2.txt").flatMap(_.split(" ")).map((_,1)).reduceByKey(_+_).sortBy(_._2,false).saveAsTextFile("C:\\Users\\37916\\Desktop\\3.txt")
    //val res = sc.textFile("C:\\Users\\37916\\Desktop\\2.txt").flatMap(_.split(" ")).map((_,1)).reduceByKey(_+_).sortBy(_._2,false)
   // println("---------"+res.collect().toBuffer)
    println(sc.textFile("C:\\Users\\37916\\Desktop\\3.txt").map(_.split(" ")).collect().toBuffer)
    println(sc.textFile("C:\\Users\\37916\\Desktop\\3.txt").flatMap(_.split(" ")).collect().toBuffer)
    sc.stop()
  }
}
