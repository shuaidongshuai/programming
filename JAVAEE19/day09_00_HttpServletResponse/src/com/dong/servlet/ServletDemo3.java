package com.dong.servlet;

import java.io.FileInputStream;
import java.io.IOException;
import java.net.URLEncoder;

import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

//实现图片下载
public class ServletDemo3 extends HttpServlet {

	/*public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		//获取图片绝对路径
		String path = getServletContext().getRealPath("/WEB-INF/classes/金莎.jpg");
		//获取图片的输入流
		FileInputStream fis = new FileInputStream(path);
		//创建字节输出流
		ServletOutputStream os = response.getOutputStream();
		
		//进行拷贝
		int len = 0;
		byte[] b = new byte[1024];
		while((len = fis.read(b))!=-1){
			os.write(b, 0, len);
		}
		//可以不用关，服务器会自关闭
		os.close();
		fis.close();
		//这样做的话就是直接在网页上面显示图片
	}*/
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		//获取图片绝对路径
		String path = getServletContext().getRealPath("/WEB-INF/classes/金莎.jpg");
		//获取图片的输入流
		FileInputStream fis = new FileInputStream(path);
		//创建字节输出流
		ServletOutputStream os = response.getOutputStream();
		
		//System.out.println(path);//D:\tomcat-7.0.52\webapps\day09_00_HttpServletResponse\WEB-INF\classes\金莎.jpg
		//获得要下载的文件名
		String filename = path.substring(path.lastIndexOf("\\")+1);//注意windows中是  \  进行文件夹分隔
		//设置文件名的编码
		String filename2 = URLEncoder.encode(filename, "UTF-8");
		//告诉客服端这是一个下载的东西
		response.setHeader("content-disposition", "attachment;filename="+filename2);
		response.setHeader("content-type", "image/jpeg");
		
		//进行拷贝
		int len = 0;
		byte[] b = new byte[1024];
		while((len = fis.read(b))!=-1){
			os.write(b, 0, len);
		}
		os.close();
		fis.close();
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);
	}

}
