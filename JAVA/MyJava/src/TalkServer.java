import java.io.*;
import java.net.*;
import java.applet.Applet;

public class TalkServer {
	public static void main(String args[]) {
		try {
			ServerSocket server = null;
			try {
				server = new ServerSocket(4700);
			} catch (Exception e) {
				System.out.println("can not listen to:" + e);
			}
			Socket socket = null;
			try {
				socket = server.accept();
			} catch (Exception e) {
				System.out.println("Error." + e);
			}
			String line;
			BufferedReader is = new BufferedReader(new InputStreamReader(
					socket.getInputStream()));
			PrintWriter os = new PrintWriter(socket.getOutputStream());
			BufferedReader sin = new BufferedReader(new InputStreamReader(
					System.in));
			System.out.println("Client:" + is.readLine());
			line = sin.readLine();
			while (!line.equals("bye")) {
				os.println(line);
				os.flush();
				System.out.println("Server:" + line);
				// 在系统标准输出上打印读入的字符串
				System.out.println("Client:" + is.readLine());
				// 从Client读入一字符串，并打印到标准输出上
				line = sin.readLine();
				// 从系统标准输入读入一字符串
			} // 继续循环
			os.close(); // 关闭Socket输出流
			is.close(); // 关闭Socket输入流
			socket.close(); // 关闭Socket
			server.close(); // 关闭ServerSocket
		} catch (Exception e) {
			System.out.println("Error:" + e);
		}
	}
}
