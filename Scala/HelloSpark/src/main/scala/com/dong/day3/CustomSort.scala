package com.dong.day3

import org.apache.spark.{SparkConf, SparkContext}

object OrderContext {
  implicit val girlOrdering = new Ordering[Girl] {
    override def compare(x: Girl, y: Girl): Int = {
      if (x.faceValue == y.faceValue) {
        y.age - x.age
      } else {
        x.faceValue - y.faceValue
      }
    }
  }
}
/**
  * Created by ☆东★ on 2016/12/31.
  */
object CustomSort {
  def main(args: Array[String]): Unit = {
    val conf = new SparkConf().setAppName("CustomSort").setMaster("local[2]")
    val sc = new SparkContext(conf)
    val rdd1 = sc.parallelize(List(("yuihatano", 90, 28, 1), ("angelababy", 90, 27, 2), ("JuJingYi", 95, 22, 3)))
    //第一种方法
    //val rdd2 = rdd1.sortBy(x => Girl(x._2,x._3), false)
    //第二种方法
    import OrderContext.girlOrdering
    val rdd2 = rdd1.sortBy(x => Girl(x._2,x._3))
    println(rdd2.collect().toBuffer)
    sc.stop()
  }
}

/**
  * 第一中方法
  * 继承Ordered 实现compare方法
  * *
  **/
//case class Girl(val faceValue: Int, val age: Int) extends Ordered[Girl] with Serializable {
//  // 想让this放在前面就返回正 ， 否则返回负数
//  override def compare(that: Girl): Int = {
//    if (this.faceValue == that.faceValue) {
//      that.age - this.age //年龄小的排在前面
//
//    } else {
//      this.faceValue - that.faceValue //颜值高的排在前面
//    }
//  }
//}

/**
  * 第二种，通过隐式转换完成排序
  */
case class Girl(faceValue: Int, age: Int) extends Serializable



