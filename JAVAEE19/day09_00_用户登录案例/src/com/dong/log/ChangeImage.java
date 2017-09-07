package com.dong.log;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.util.Random;

import javax.imageio.ImageIO;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import cn.dsna.util.images.ValidateCode;


public class ChangeImage extends HttpServlet {

	//ValidateCode.jar 包 创建图像，别人都封装好了
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		//告诉各种浏览器不使用缓存(可以在index，jsp中直接拷贝，都有)
		response.setHeader("pragma", "no-cache");
		response.setHeader("cache-control", "no-cache");
		response.setHeader("expires", "0");
		
		ValidateCode vc = new ValidateCode(200, 50, 4, 20);
		//ValidateCode vc = new ValidateCode(110, 25, 4, 9);
		vc.write(response.getOutputStream());
		
		//获取验证码的值
		String code = vc.getCode();
		System.out.println(code);
	}

	//自己写验证码图片
	private void myImage(HttpServletResponse response) throws IOException {
		//在内存中创建一个图像对象
		int width = 200;
		int height = 100;
		BufferedImage img = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
		//创建一个画笔
		Graphics g = img.getGraphics();
		//给图片一个背景色
		g.setColor(Color.GRAY);
		g.fillRect(0, 0, width, height);
		g.setColor(Color.PINK);
		g.fillRect(10, 10, width-20, height-20);
		
		//设置文本样式
		g.setColor(Color.BLUE);
		g.setFont(new Font("宋体", Font.BOLD|Font.ITALIC, 70));//bold	加粗	italic 斜体 
		
		//给图片添加文本
		Random random = new Random();
		for (int i = 0; i < 4; i++) {
			g.drawString(random.nextInt(10)+"", 15+40*i, 75);
		}
		
		//添加干扰线
		for (int i = 0; i < 20; i++) {
			g.drawLine(random.nextInt(width), random.nextInt(height), random.nextInt(width), random.nextInt(height));
		}
		
		//将图片对象以流的方式输出的客户端
		ImageIO.write(img, "png", response.getOutputStream());
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);
	}

}
