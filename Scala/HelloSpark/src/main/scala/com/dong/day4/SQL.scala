package com.dong.day4

import org.apache.spark.sql.SQLContext
import org.apache.spark.{SparkConf, SparkContext}

/**
  * Created by ☆东★ on 2017/1/2.
  */
object SQL {
  def main(args: Array[String]): Unit = {
    val conf = new SparkConf().setAppName("SQL").setMaster("local[2]")
    val sc = new SparkContext(conf)
    //创建SQLContext
    val sqlContext = new SQLContext(sc)
    //为这个程序增加权限，可以在hdfs中读取数据
    System.setProperty("user.name","root")

    val personRDD = sc.textFile("hdfs://mini1:9000/person.txt").map(line => {
      val split = line.split(",")
      //4.将RDD和case class关联
      Person(split(0).toLong,split(1),split(2).toInt)
    })
    import sqlContext.implicits._
    val personDF = personRDD.toDF

    // DSL风格语法
    personDF.show
    personDF.select("name").show()
    //按年龄进行分组并统计相同年龄的人数
    personDF.groupBy("age").count().show()

    println("------------------------------------------------------------")

    //2.3.2.	SQL风格语法
    personDF.registerTempTable("person")
    sqlContext.sql("select * from person where age >= 20 order by age desc limit 2").show()

    sc.stop()
  }
}
case class Person(id: Long,name: String,age: Int)
