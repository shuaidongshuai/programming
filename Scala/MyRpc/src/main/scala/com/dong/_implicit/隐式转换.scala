package com.dong._implicit

import java.io.File

import scala.io.Source

/**
  * Created by ☆东★ on 2016/12/21.
  */

object MyPredef {
  implicit def fileToRichFile(f: File) = new 隐式转换(f)
}

class 隐式转换(val f: File) {
  def read() = Source.fromFile(f).mkString
}

/**
  * 目的：当我们调用File的时候想直接使用read
  */
object 隐式转换 {
  val f = new File("E:\\study_materials\\Bdata\\day27\\dong.txt")

  def main1(args: Array[String]): Unit = {
    //装饰模式
    val context = new 隐式转换(f).read()
    println(context)
  }

  def main(args: Array[String]): Unit = {
    //隐式转化
    import MyPredef._
    val context = f.read()
    println(context)
  }
}
