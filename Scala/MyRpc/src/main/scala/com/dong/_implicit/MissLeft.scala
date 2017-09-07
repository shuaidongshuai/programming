package com.dong._implicit
/**
  * Created by ☆东★ on 2016/12/22.
  */
class MissLeft[T: Ordering] {
  def choose(first: T, second: T): T = {
    val ord = implicitly[Ordering[T]]
    if(ord.gt(first,second)) first else second
  }
}
object MissLeft{
//  def main(args: Array[String]): Unit = {
//    val ml = new MissLeft[Girl]
//    val g1 = new Girl("hello", 98)
//    val g2 = new Girl("Tom", 95)
//    val g = ml.choose(g1, g2)
//    println(g.name)
//  }
}
