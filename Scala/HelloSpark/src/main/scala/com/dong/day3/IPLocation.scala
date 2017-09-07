package com.dong.day3

import java.sql.{Connection, Date, DriverManager, PreparedStatement}

import org.apache.spark.{SparkConf, SparkContext}

/**
  * Created by ☆东★ on 2016/12/31.
  */
object IPLocation {
  def ip2Long(ip: String): Long = {
    val fragments = ip.split("[.]")
    var ipNum = 0L
    for (i <- 0 until fragments.length) {
      ipNum = fragments(i).toLong | ipNum << 8L //注意： << 优先级比  | 高
    }
    ipNum
  }

  def binarySearch(lines: Array[(String, String, String)], ip: Long): Int = {
    var low = 0
    var hight = lines.length - 1
    while (low <= hight) {
      val middle = (low + hight) / 2
      if (ip >= lines(middle)._1.toLong && ip <= lines(middle)._2.toLong)
        return middle
      if (ip < lines(middle)._1.toLong)
        hight = middle - 1
      else
        low = middle + 1
    }
    -1
  }

  val data2MySQL = (iterator: Iterator[(String, Int)]) => {
    var conn: Connection = null
    var ps: PreparedStatement = null
    val sql = "INSERT INTO ip_count(location,COUNT,DATE) VALUES(?,?,?)"
    conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/big_data","root","dong")
    //遍历传进来分区的集合，放入数据库
    iterator.foreach(line => {
      ps = conn.prepareStatement(sql)
      ps.setString(1,line._1)
      ps.setInt(2,line._2)
      ps.setDate(3,new Date(System.currentTimeMillis()))
      ps.executeUpdate()//执行
    })
    ps.close()
    conn.close()
  }

  def main(args: Array[String]): Unit = {
    val conf = new SparkConf().setAppName("IPLocation").setMaster("local[2]")
    val sc = new SparkContext(conf)

    val ipRulesRdd = sc.textFile("E:\\study_materials\\Bdata\\资料\\day30\\计算IP地址归属地\\ip.txt").map(line => {
      val fields = line.split("\\|")
      // | 在正则中是关键字，如果要实现以“|”作为分割符，那么应该输入“\|”，而不是“|”。
      val start_num = fields(2)
      val end_num = fields(3)
      val province = fields(6)
      (start_num, end_num, province)
    })
    //全部的ip映射规则
    val ipRulesArray = ipRulesRdd.collect()
    //广播规则   把所有ip和属性都广播出去
    val ipRulesBroadcast = sc.broadcast(ipRulesArray)

    //加载要处理的数据
    val ipsRdd = sc.textFile("E:\\study_materials\\Bdata\\资料\\day30\\计算IP地址归属地\\20090121000132.log").map(line => {
      val fields = line.split("\\|")
      fields(1)
    })
    val result = ipsRdd.map(ip => {
      val ipNum = ip2Long(ip)
      val index = binarySearch(ipRulesBroadcast.value, ipNum)
      //在广播的内存中，找到ipNum在value中的索引
      val info = ipRulesBroadcast.value(index) //获取ipNum的属性
      (info._3, 1) //统计省份
    }).reduceByKey(_ + _)
    println(result.collect().toBuffer)
    //向MySQL写入数据
    result.foreachPartition(data2MySQL)
    //result.foreachPartition(data2MySQL(_))  //上面是下面的简写，dada2MySQL要传入一个iterator参数，而foreach正好可以给他这个参数
    sc.stop()
  }
}
/*
  foreachPartition要一个f: Iterator[T] => Unit这样的函数，而data2MySQL正好符合，而且data2MysSQL需要的参数就是result
 */
