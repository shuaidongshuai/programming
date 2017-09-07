package com.dong._implicit

/**
  * Created by ☆东★ on 2016/12/22.
  */
class MissRight[T] {
                                  //要传一个隐式转化的函数进来
  def choose(first: T, second: T)(implicit ord : T => Ordered[T]): T = {
    if(first > second) first else second
  }
                                  //要传一个隐式转化的值进来
  def select(first: T, second: T)(implicit ord : Ordering[T]): T ={
    if(ord.gt(first, second)) first else second
  }

  def random(first: T, second: T)(implicit ord : Ordering[T]): T ={
    import Ordered.orderingToOrdered
    if(first > second) first else second
  }
}
object MissRight {
  def main(args: Array[String]) {
    val mr = new MissRight[Girl]
    val g1 = new Girl("hatanao", 98)
    val g2 = new Girl("sora", 95)

    import MyPreDef.girlOrdering
    var g = mr.choose(g1, g2)
    println(g.name)
    g = mr.select(g1, g2)
    println(g.name)
  }
}
