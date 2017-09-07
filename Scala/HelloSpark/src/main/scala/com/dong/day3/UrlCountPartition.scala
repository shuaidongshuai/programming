package com.dong.day3

import java.net.URL

import org.apache.spark.{Partitioner, SparkConf, SparkContext}

import scala.collection.mutable

/**
  * Created by ☆东★ on 2016/12/31.
  */
object UrlCountPartition {
  def main(args: Array[String]): Unit = {
    val conf = new SparkConf().setAppName("UrlCountPartition").setMaster("local[2]")
    val sc = new SparkContext(conf)
    //rdd1将数据切分，元组中放的是（URL， 1）
    val rdd1 = sc.textFile("E:\\study_materials\\Bdata\\资料\\day29\\itcast.log").map(line => {
      val split = line.split("\t")
      (split(1), 1)
    })
    val rdd2 = rdd1.reduceByKey(_ + _)
    val rdd3 = rdd2.map(t => {
      val url = t._1
      val host = new URL(url).getHost
      (host, (url, t._2))
    })
    // (php.itcast.cn,(http://php.itcast.cn/php/course.shtml,459)),
    // (java.itcast.cn,(http://java.itcast.cn/java/course/base.shtml,543)),
    val rdd4 = rdd3.map(_._1)
    //php.itcast.cn, java.itcast.cn, java.itcast.cn, java.itcast.cn, net.itcast.cn, java.itcast.cn, net.itcast.cn,
    val ints = rdd4.distinct().collect //去重
    //net.itcast.cn, java.itcast.cn, php.itcast.cn

    //val rdd5 = rdd3.partitionBy(new HashPartitioner(ints.length)) //Hash值有重复
    val hostPartitioner = new HostParitioner(ints)
    val rdd5 = rdd3.partitionBy(hostPartitioner)
    //如果要排序，取最大的三个保存，那么就要用mapPartitions对分区内容排序
    val rdd6 = rdd5.mapPartitions(it =>{
      it.toList.sortBy(_._2._2).reverse.take(3).iterator
    })

    rdd5.saveAsTextFile("E:\\study_materials\\Bdata\\day30\\out2")
   // println(rdd5.collect().toBuffer)
  }
}

class HostParitioner(ins: Array[String]) extends Partitioner {
  val partMap = new mutable.HashMap[String, Int]()
  var count = 0
  for (i <- ins) {
    partMap += (i -> count)
    count += 1
  }

  override def numPartitions: Int = ins.length

  override def getPartition(key: Any): Int = {
    partMap.getOrElse(key.toString, 0)
  }
}

/*
  def getOrElse[B1 >: B](key: A, default: => B1): B1 = get(key) match {
    case Some(v) => v
    case None => default
  }
 */
