package com.dong.proxy;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;

/**
 * 需要代理的接口
 */
interface Worker {
	public void Add(int a, int b);
}

/**
 * 实际对象
 */
class WorkerImpl implements Worker {

	@Override
	public void Add(int a, int b) {
		System.out.println(a + "+" + b + "=" + (a + b));
	}

}

/**
 * 调用处理器实现类 每次生成动态代理类对象时都需要指定一个实现了该接口的调用处理器对象
 */
class InvocationHandlerImpl {
	/**
	 * 这个就是我们要代理的真实对象
	 */
	private Object target;

	/**
	 * 构造方法
	 * 
	 * @param target
	 */
	public InvocationHandlerImpl(Object target) {
		super();
		this.target = target;
	}

	public Object getProxyInstance() {
		return Proxy.newProxyInstance(InvocationHandlerImpl.class
				.getClassLoader(), target.getClass().getInterfaces(),
				new InvocationHandler() {
					@Override
					public Object invoke(Object proxy, Method method,
							Object[] args) throws Throwable {
						// 在目标对象的方法执行之前简单的打印一下
						System.out
								.println("------------------before------------------");
						System.out.println("Method:" + method);
						// 执行目标对象的方法
						Object result = method.invoke(target, args);
						// 在目标对象的方法执行之后简单的打印一下
						System.out
								.println("-------------------after------------------");
						return result;
					}
				});
	}
}

public class ProxyDemo {
	public static void main(String[] args) {
		// 实例化目标对象
		Worker worker = new WorkerImpl();
		// 实例化InvocationHandler
		InvocationHandlerImpl invocationHandlerImpl = new InvocationHandlerImpl(
				worker);
		// 根据目标对象生成代理对象
		Worker proxy = (Worker) invocationHandlerImpl.getProxyInstance();
		// 调用代理对象的方法
		proxy.Add(10, 12);
	}
}
