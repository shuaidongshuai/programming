package com.dong.day2

import org.apache.spark.{SparkConf, SparkContext}

/**
  * Created by ☆东★ on 2016/12/30.
  */
object AdvUserLocation {
  def main(args: Array[String]): Unit = {
    val conf = new SparkConf().setAppName("AdvUserLocation").setMaster("local[2]")
    val sc = new SparkContext(conf)
    val rdd0 = sc.textFile("E:\\study_materials\\Bdata\\资料\\day28\\练习\\bs_log").map(line => {
      val fields = line.split(",")
      val eventType = fields(3)
      val time = fields(1)
      val timeLong = if (eventType == "1") -time.toLong else time.toLong
      ((fields(0), fields(2)), timeLong)
    })
    //((18688888888,16030401EAFB68F1E3CDF819735E1C66),-20160327082400),
    // ((18611132889,16030401EAFB68F1E3CDF819735E1C66),-20160327082500),
    // ((18688888888,16030401EAFB68F1E3CDF819735E1C66),20160327170000),
    // ((18611132889,16030401EAFB68F1E3CDF819735E1C66),20160327180000),
    val rdd1 = rdd0.reduceByKey(_ + _).map(t => {
      val mobile = t._1._1
      val lac = t._1._2
      val time = t._2
      (lac, (mobile, time))
    })
    //(CC0710CC94ECC657A8561DE549D940E0,(18688888888,1300)),
    // (9F36407EAD0629FC166F14DDE7970F68,(18611132889,54000)),
    // (9F36407EAD0629FC166F14DDE7970F68,(18688888888,51200))
    val rdd2 = sc.textFile("E:\\study_materials\\Bdata\\资料\\day28\\练习\\lac_info.txt").map(line => {
      val f = line.split(",")
      //(基站ID， （经度，纬度）)
      (f(0), (f(1), f(2)))
    })
    //val rdd3 = rdd1.join(rdd2)
    //(CC0710CC94ECC657A8561DE549D940E0,((18688888888,1300),(116.303955,40.041935))),
    // (CC0710CC94ECC657A8561DE549D940E0,((18611132889,1900),(116.303955,40.041935)))
    val rdd3 = rdd1.join(rdd2).map(t => {
      val lac = t._1
      val mobile = t._2._1._1
      val time = t._2._1._2
      val x = t._2._2._1
      val y = t._2._2._2
      (mobile, lac, time, x, y)
    })
    //(18688888888,CC0710CC94ECC657A8561DE549D940E0,1300,116.303955,40.041935),
    // (18611132889,CC0710CC94ECC657A8561DE549D940E0,1900,116.303955,40.041935)
    val rdd4 = rdd3.groupBy(_._1)
    //按电话号码进行分组
    //(18688888888,CompactBuffer((18688888888,CC0710CC94ECC657A8561DE549D940E0,1300,116.303955,40.041935), (18688888888,16030401EAFB68F1E3CDF819735E1C66,87600,116.296302,40.032296), (18688888888,9F36407EAD0629FC166F14DDE7970F68,51200,116.304864,40.050645))),
    val rdd5 = rdd4.mapValues(it => {
      //it.toList
      //(18688888888,List((18688888888,CC0710CC94ECC657A8561DE549D940E0,1300,116.303955,40.041935), (18688888888,16030401EAFB68F1E3CDF819735E1C66,87600,116.296302,40.032296), (18688888888,9F36407EAD0629FC166F14DDE7970F68,51200,116.304864,40.050645))),
      it.toList.sortBy(_._3).reverse.take(2)
    })
    // (18688888888,List((18688888888,16030401EAFB68F1E3CDF819735E1C66,87600,116.296302,40.032296),
    // (18688888888,9F36407EAD0629FC166F14DDE7970F68,51200,116.304864,40.050645))),
    // (18611132889,List((18611132889,16030401EAFB68F1E3CDF819735E1C66,97500,116.296302,40.032296),
    // (18611132889,9F36407EAD0629FC166F14DDE7970F68,54000,116.304864,40.050645)))
    println(rdd4.collect.toBuffer)
    println("----------------------------------------------")
    println(rdd5.collect.toBuffer)
    sc.stop()
  }
}
