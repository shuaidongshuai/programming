package com.dong._implicit

/**
  * Created by ☆东★ on 2016/12/22.
  */
object MyPreDef {
  implicit object girlOrdering extends Ordering[Girl] {
    override def compare(x: Girl, y: Girl): Int = {
      x.faceValue - y.faceValue
    }
  }
}
