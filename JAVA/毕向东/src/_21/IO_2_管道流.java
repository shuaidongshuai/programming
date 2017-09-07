package _21;

import java.io.IOException;
import java.io.PipedInputStream;
import java.io.PipedOutputStream;

class Read implements Runnable{
	private PipedInputStream pis;
	Read(PipedInputStream pis){
		this.pis = pis;
	}
	public void run(){
		try {
			byte[] buf = new byte[1024];
			System.out.println("什么都没哟读到");
			int len = pis.read(buf);
			System.out.println("read finish");
			String s = new String(buf,0,len);
			System.out.println("Read:"+s);
			pis.close();
		} catch (Exception e) {
			System.out.println("读取失败");
		}
	}
}
class Write implements Runnable{
	private PipedOutputStream pos;
	Write(PipedOutputStream pos){
		this.pos = pos;
	}
	public void run(){
		try {
			System.out.println("正在写入，等在6秒");
			Thread.sleep(6000);
			pos.write("hello dong".getBytes());
			System.out.println("finished Write");
			pos.close();
			
		} catch (Exception e) {
			System.out.println("write失败");
		}
	}
}

public class IO_2_管道流 {
	public static void main(String[] args) throws Exception {
		PipedInputStream pis = new PipedInputStream();
		PipedOutputStream pos = new PipedOutputStream(pis);
		
		Read r = new Read(pis);
		Write w = new Write(pos);
		
		new Thread(r).start();
		new Thread(w).start();
	}
}
