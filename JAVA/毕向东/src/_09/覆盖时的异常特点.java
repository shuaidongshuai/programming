package _09;
/*
 * 异常在字符类中的体现
 * 1,子类再覆盖父类时，如果父类的方法抛出异常，那么子类的覆盖方法，只能抛出父类的异常或者该异常的子类
 * 2,如果父类方法抛出多个异常，那么之类在覆盖该方法时，只能抛出父类异常的子集
 * 3,如果父类或者接口的方法中没有异常抛出，那么子类覆盖方法时，也不可以抛出异常
 * 		如果子类方法发生异常，就必须进行try处理，绝对不能抛
 * 
 * 
 * 如果子类抛出父类没有的异常
 * 那么这就叫做：
 * 早起的程序不能处理后期产生的新异常。
 */
//	Such as
/*
 * class AException extends Exception
 * {
 * }
 * class BException extends Exception
 * {
 * }
 * class cException extends Exception
 * {
 * }
 * class Fu
 * {
 * 		void show()throws AException,BException
 * 		{
 * 		}
 * }
 * class Zi extends Fu
 * {
 * 		void show()throw 这里只能抛出父类异常的子集，不能抛出  C  异常
 * 		{
 * 			如果这里真的有 C 异常。。那么就必须在这个子类中自己用   try{}catch{} 处理
 * 		}
 * }
 * 
 */


public class 覆盖时的异常特点 {

}
