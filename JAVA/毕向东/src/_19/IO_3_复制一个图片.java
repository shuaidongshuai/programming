package _19;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

/*
 * 
 */
public class IO_3_复制一个图片 {
	public static void main(String[] args) {
		FileOutputStream fos = null;
		FileInputStream fis = null;
		
		try {
			fis = new FileInputStream("C:\\Users\\37916\\Pictures\\Camera Roll\\东.jpg");//读
			fos = new FileOutputStream("C:\\Users\\37916\\Desktop\\1.png");					//写	
			
			byte[] buf = new byte[1024];
			int len = 0;
			while((len = fis.read(buf))!= -1){//从此输入流中将最多 buf.length 个字节的数据读入一个 byte 数组中   如果没哟参数就是读一个字节
				fos.write(buf,0,len);
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} finally{
			if(fos == null)
				try {
					fos.close();
				} catch (Exception e2) {
					// TODO: handle exception
				}
			if(fis == null)
				try {
					fis.close();
				} catch (Exception e2) {
					// TODO: handle exception
				}
		}
		
		
	}
}
