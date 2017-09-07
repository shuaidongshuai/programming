package com.dong.test

import org.apache.spark.{SparkConf, SparkContext}

/**
  * Created by ☆东★ on 2017/1/3.
  */
object WordCount {
  def main(args: Array[String]): Unit = {
    test()
  }
  def test(): Unit ={
    val conf = new SparkConf().setAppName("WordCount").setMaster("local[2]")
    val sc = new SparkContext(conf)
    val rdd1 = sc.textFile("C:\\Users\\37916\\Desktop\\11.txt").flatMap(_.split(" ")).map((_,1)).reduceByKey(_+_)
    println(rdd1.collect().toBuffer)
    sc.stop()
  }
}
