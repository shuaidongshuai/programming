package com.dong.day3

import java.sql.DriverManager

import org.apache.spark.rdd.JdbcRDD
import org.apache.spark.{SparkConf, SparkContext}

/**
  * Created by ☆东★ on 2017/1/1.
  */
object JdbcRDDDemo {
  def main(args: Array[String]): Unit = {
    val conf = new SparkConf().setAppName("JdbcRDDDemo").setMaster("local[2]")
    val sc = new SparkContext(conf)
    val connection =() => {
      Class.forName("com.mysql.jdbc.Driver").newInstance()
      DriverManager.getConnection("jdbc:mysql://localhost:3306/big_data","root","dong")
    }
    val jdbcRDD = new JdbcRDD(
      sc,
      connection,
      "select * from ip_count where id >= ? and id <= ?",
      9,11,2,
      r => {
        (r.getString(2),r.getInt(3))
      }
    )
    println(jdbcRDD.collect().toBuffer)
    sc.stop()
  }
}
