package com.dong.javap;

/**
 * @author dong
 */
public class TestCommand {

    public static void main(String[] args) {
        int a = 1;
        int b = 2;
        int c = a + b;
    }
}
/*
dong@ali-1c36bb15e1ba  ~/Documents/code/MyJava  javap -verbose target.classes.com.dong.javap.TestCommand
警告: 二进制文件target.classes.com.dong.javap.TestCommand包含com.dong.javap.TestCommand
Classfile /Users/dong/Documents/code/MyJava/target/classes/com/dong/javap/TestCommand.class
  Last modified 2018-11-18; size 472 bytes
  MD5 checksum c2164223fe0433929bf19745623e0e79
  Compiled from "TestCommand.java"
public class com.dong.javap.TestCommand
  minor version: 0
  major version: 52
  flags: ACC_PUBLIC, ACC_SUPER
Constant pool:
   #1 = Methodref          #3.#21         // java/lang/Object."<init>":()V
   #2 = Class              #22            // com/dong/javap/TestCommand
   #3 = Class              #23            // java/lang/Object
   #4 = Utf8               <init>
   #5 = Utf8               ()V
   #6 = Utf8               Code
   #7 = Utf8               LineNumberTable
   #8 = Utf8               LocalVariableTable
   #9 = Utf8               this
  #10 = Utf8               Lcom/dong/javap/TestCommand;
  #11 = Utf8               main
  #12 = Utf8               ([Ljava/lang/String;)V
  #13 = Utf8               args
  #14 = Utf8               [Ljava/lang/String;
  #15 = Utf8               a
  #16 = Utf8               I
  #17 = Utf8               b
  #18 = Utf8               c
  #19 = Utf8               SourceFile   //dong:调试文件。默认命令是javap -g: source，如果是javap -g: none 将没有这个文件
  #20 = Utf8               TestCommand.java
  #21 = NameAndType        #4:#5          // "<init>":()V
  #22 = Utf8               com/dong/javap/TestCommand
  #23 = Utf8               java/lang/Object
{
  public com.dong.javap.TestCommand();
    descriptor: ()V
    flags: ACC_PUBLIC
    Code:
      stack=1, locals=1, args_size=1
         0: aload_0
         1: invokespecial #1                  // Method java/lang/Object."<init>":()V
         4: return
      LineNumberTable:
        line 6: 0
      LocalVariableTable:
        Start  Length  Slot  Name   Signature
            0       5     0  this   Lcom/dong/javap/TestCommand;

  public static void main(java.lang.String[]);
    descriptor: ([Ljava/lang/String;)V
    flags: ACC_PUBLIC, ACC_STATIC
    Code:
      stack=2, locals=4, args_size=1
         0: iconst_1    //dong:将int类型的值1 推到栈顶
         1: istore_1    //赋值给solt第1个位置的变量(第0个位置的变量是String[] args)(如果是非静态方法this将作为第0个位置)
         2: iconst_2
         3: istore_2
         4: iload_1     //将solt-1变量值推至栈顶
         5: iload_2
         6: iadd        //计算add后把值放在栈顶
         7: istore_3    //将结果从栈顶取出，放到solt-3
         8: return
      LineNumberTable:  //调试使用
        line 9: 0
        line 10: 2
        line 11: 4
        line 12: 8
      LocalVariableTable:   //本地变量列表
        //1.本地变量虚拟指令作用域的起始位置2.作用域的长度3.solt起始位置编号(long/double占2个solt)4.变量名5.类型
        Start  Length  Slot  Name   Signature
            0       9     0  args   [Ljava/lang/String;     //第一个变量args是从0开始的
            2       7     1     a   I
            4       5     2     b   I
            8       1     3     c   I
}
//dong:上面这些指令是JVM的虚拟指令，他们可能会重新排序某些原来的代码顺序
虚拟指令 -> CPU的指令 阶段可能会被再次重新排序
 */