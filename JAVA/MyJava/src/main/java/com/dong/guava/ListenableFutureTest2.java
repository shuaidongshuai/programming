package com.dong.guava;

import com.google.common.util.concurrent.*;
import org.junit.Test;

import java.util.concurrent.*;
import java.util.function.Consumer;
import java.util.function.Function;

/**
 * @author com.dong
 * 为了适配hsf的异步调用，hsf使用的是future
 * 发起hsf调用，基本都是同时发起的
 * 这样设计可以无缝的执行一个又一个的函数，拿到上一个future结果就执行下一个函数
 * 如果每一个函数里面都是RPC异步调用，那么主线程很快就执行完了，所有RPC请求也都发出去了，接下来就只是等待每个RPC的返回值
 */
public class ListenableFutureTest2{
    /**
     * 线程池中线程个数
     */
    private static final int POOL_SIZE = 50;
    /**
     * 带有回调机制的线程池
     */
    private static final ListeningExecutorService service = MoreExecutors.listeningDecorator(Executors.newFixedThreadPool(POOL_SIZE));

    @Test
    public void testListenableFuture() throws ExecutionException, InterruptedException {
        DongFuture<String> dongFuture = new DongFuture<>(service);
        dongFuture.setResult("这里可以放一个hsf调用的future");
        DongFuture<String> dongFuture1 = dongFuture.thenApplyAsync(r -> {
            Thread.sleep(1000);
            String res = "1收到：" + r;
            System.out.println(res);
            return DongFuture.finishResult(res);
        }).thenApplyAsync(r -> {
            String res = "2收到：" + r;
            System.out.println(res);
            return DongFuture.finishResult(res);
        });

        DongFuture<String> dongFuture2 = dongFuture.thenApply(r -> {
            String res = "3收到：" + r;
            System.out.println(res);
            return res;
        }).thenApply(r -> {
            String res = "4收到：" + r;
            System.out.println(res);
            return res;
        });

        //get会阻塞 -- hsf异步化的时候不需要get -- 在thenApply中就可以把数据写回去
        String res1 = dongFuture1.get();
        System.out.println("获取最终结果：" + res1);
        String res2 = dongFuture2.get();
        System.out.println("获取最终结果：" + res2);
    }

    @Test
    public void testException() throws ExecutionException, InterruptedException {
        DongFuture<String> dongFuture = new DongFuture<>(service);
        dongFuture.setResult("初始值");

        DongFuture<String> dongFuture1 = dongFuture.thenApplyAsync(r -> {
            int a = 1 / 0;
            return DongFuture.finishResult(1);
        }).thenApply(r -> {
            String res = "1收到：" + r;
            System.out.println(res);
            return res;
        }).exceptionally(e -> {
            System.out.println("1收到一个异常：" + e);
            return "com.dong-异常";
        });

        DongFuture<String> dongFuture2 = dongFuture.thenApplyAsync(r -> {
            throw new Exception("随便抛个异常");
        }).exceptionally(e -> {
            System.out.println("2收到一个异常：" + e);
        });

        try {
            String res1 = dongFuture1.get();
            System.out.println("获取最终结果：" + res1);
        }catch (Exception e){
            System.out.println("1发生异常 " + e);
        }
        try {
            String res2 = dongFuture2.get();
            System.out.println("获取最终结果：" + res2);
        }catch (Exception e){
            System.out.println("2发生异常 " + e);
        }
    }

    @Test
    public void testTimeout() throws ExecutionException, InterruptedException {
        DongFuture<String> dongFuture = new DongFuture<>(service);
        dongFuture.setResult("初始值");

        DongFuture<String> dongFuture1 = dongFuture.thenApplyAsync(r -> {
            Thread.sleep(10_000);
            return DongFuture.finishResult(1);
        }).thenApply(r -> {
            String res = "1收到：" + r;
            System.out.println(res);
            return res;
        }).exceptionally(e -> {
            System.out.println("1收到一个异常：" + e);
            return "com.dong-异常";
        }).timeout(t -> {
            System.out.println("已经超时：2s");
        }, 2000L);

        try {
            dongFuture1.get();
        }catch (Exception e){
            System.out.println("发生异常：" + e);
        }
    }
}

class DongFuture<T> extends AbstractFuture<T> {
    protected Executor executor;

    DongFuture(Executor executor){
        this.executor = executor;
    }

    public void setResult(T t){
        set(t);
    }

    public static <U> ListenableFuture<U> finishResult(U t){
        return Futures.immediateFuture(t);
    }

    public <U> DongFuture<U> thenApplyAsync(AsyncFunction<? super T, ? extends U> func){
        ChainFuture<T, U> chainFuture = new ChainFuture<T, U>(this, func);
        addListener(chainFuture, executor);
        return chainFuture;
    }

    public <U> DongFuture<U> thenApply(Function<? super T, ? extends U> func){
        return thenApplyAsync(function2Async(func));
    }

    public <U> AsyncFunction<? super T, ? extends U> function2Async(Function<? super T, ? extends U> func){
        return (input) -> {
            U output = func.apply(input);
            return Futures.immediateFuture(output);
        };
    }

    /**
     * 带返回值的异常
     * @param func
     * @param <U>
     * @return
     */
    public <U> DongFuture<U> exceptionally(Function<Throwable, ? extends U> func){
        ExeceptionReturnFuture<U> execeptionReturnFuture = new ExeceptionReturnFuture<U>(this, func);
        addListener(execeptionReturnFuture, executor);
        return execeptionReturnFuture;
    }

    /**
     * 不带返回值的异常
     * @param func
     * @param <U>
     * @return
     */
    public <U> DongFuture<U> exceptionally(Consumer<Throwable> func){
        ExeceptionFuture<U> execeptionFuture = new ExeceptionFuture<U>(this, func);
        addListener(execeptionFuture, executor);
        return execeptionFuture;
    }

    /**
     * 超时设置
     * @param func
     * @param <U>
     * @return
     */
    public <U> DongFuture<U> timeout(Consumer<DongFuture<U>> func, long timeoutMilliSeconds){
        TimeoutFuture<U> timeoutException = new TimeoutFuture<U>(this, func, timeoutMilliSeconds);
        addListener(timeoutException, executor);
        return timeoutException;
    }

    /**
     * 为Future增加入参，把多个Future连接起来
     * @param <T>
     * @param <U>
     */
    class ChainFuture<T, U> extends DongFuture<U> implements Runnable {
        AsyncFunction<? super T, ? extends U> function;
        ListenableFuture<? extends T> inputFuture;

        ChainFuture(DongFuture inputFuture, AsyncFunction<? super T, ? extends U> function) {
            super(inputFuture.executor);
            this.inputFuture = inputFuture;
            this.function = function;
        }

        @Override
        public void run() {
            try {
                //获取上一个结果
                T result = Futures.getDone(inputFuture);
                //运行这个方法
                final ListenableFuture<? extends U>  outputFuture = function.apply(result);
                outputFuture.addListener(() -> {
                    try {
                        //获取上一个结果
                        U NextResult = Futures.getDone(outputFuture);
                        //设置下一个结果
                        set(NextResult);
                    } catch (ExecutionException e) {
                        setException(e.getCause());
                    }
                }, executor);
            } catch (Exception e) {
                setException(e);
            }
        }
    }

    /**
     * 异常处理 - 待返回值
     * @param <T>
     */
    class ExeceptionReturnFuture<T> extends DongFuture<T> implements Runnable{
        Function<Throwable, ? extends T> function;
        ListenableFuture<? extends T> inputFuture;

        ExeceptionReturnFuture(DongFuture inputFuture, Function<Throwable, ? extends T> function) {
            super(inputFuture.executor);
            this.inputFuture = inputFuture;
            this.function = function;
        }

        @Override
        public void run() {
            try {
                T result = Futures.getDone(inputFuture);
                set(result);
            } catch (Exception e) {
                set(function.apply(e.getCause()));
            }
        }
    }

    /**
     * 异常处理 - 不带返回值
     * @param <T>
     */
    class ExeceptionFuture<T> extends DongFuture<T> implements Runnable{
        Consumer<Throwable> function;
        ListenableFuture<? extends T> inputFuture;

        ExeceptionFuture(DongFuture inputFuture, Consumer<Throwable> function) {
            super(inputFuture.executor);
            this.inputFuture = inputFuture;
            this.function = function;
        }

        @Override
        public void run() {
            try {
                T result = Futures.getDone(inputFuture);
                set(result);
            } catch (Exception e) {
                function.accept(e.getCause());
                setException(e);
            }
        }
    }

    /**
     * 超时
     * @param <T>
     */
    class TimeoutFuture<T> extends DongFuture implements Runnable {
        /**
         * 延迟执行的线程池
         */
        private ScheduledExecutorService timeoutService = new ScheduledThreadPoolExecutor(2);
        Consumer<DongFuture<T>> function;
        ListenableFuture<T> inputFuture;

        TimeoutFuture(DongFuture inputFuture, Consumer<DongFuture<T>> function, long timeoutMilliSeconds) {
            super(inputFuture.executor);
            this.inputFuture = inputFuture;
            this.function = function;

            timeoutService.schedule(() -> {
                //如果没有完成任务，设置异常
                if (!inputFuture.isDone()) {
                    function.accept(inputFuture);
                    setException(new TimeoutException());
                    inputFuture.cancel(true);
                }
            }, timeoutMilliSeconds, TimeUnit.MILLISECONDS);
        }

        @Override
        public void run() {
            try {
                T result = Futures.getDone(inputFuture);
                set(result);
            } catch (Exception e) {
                setException(e);
            }
        }
    }
}