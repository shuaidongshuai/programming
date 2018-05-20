package com.dong.controller;

import java.io.PrintWriter;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Random;

import javax.servlet.http.HttpServletRequest;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.multipart.MultipartHttpServletRequest;
import org.springframework.web.multipart.commons.CommonsMultipartFile;

import com.dong.utils.Common;
import com.sun.jersey.api.client.Client;
import com.sun.jersey.api.client.WebResource;

@Controller
@RequestMapping("upload")
public class UploadController {
	@RequestMapping("uploadPic")
	public void uploadPic(HttpServletRequest request, String fileName,
			PrintWriter out) {
		// 把Request强转成多部件请求对象---因为传过来的是图片流
		MultipartHttpServletRequest mhs = (MultipartHttpServletRequest) request;
		// 根据文件名称获取文件对象
		CommonsMultipartFile cmf = (CommonsMultipartFile) mhs.getFile(fileName);
		// 获取文件上传流
		byte[] fileBytes = cmf.getBytes();
		// 获取文件扩展名
		String originalFilename = cmf.getOriginalFilename();// 全名
		if(!originalFilename.contains(".")){
			return;
		}
		String suffix = originalFilename.substring(originalFilename
				.lastIndexOf("."));// 最后一个.后面的为扩展名

		// 文件名称在服务器有可能重复--随机生成文件名
		String newFileName = "";
		SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddHHmmssSSS");
		newFileName = sdf.format(new Date());
		Random r = new Random();
		for (int i = 0; i < 3; ++i) {
			newFileName += r.nextInt(10);
		}

		// 全新的文件名(服务器地址 + 路径 + 文件名)
		String fullName = Common.PIC_HOST + "/upload/" + newFileName + suffix;

		// 创建jersey服务器，进行跨服务器上传
		Client client = Client.create();
		// 资源关联服务器的文件名
		WebResource resource = client.resource(fullName);
		// 上传
		resource.put(fileBytes);

		/* ajax回调函数需要回写
		 1.图片回显:服务器图片完整路径
		 2.数据库：图片的相对路径
		 3.会写格式：json {"":"","":""}
		 */
		String relativePath = "/upload/" + newFileName + suffix;
		String resStr = "{\"fullName\":\"" + fullName
				+ "\", \"relativePath\":\"" + relativePath + "\"}";
		out.print(resStr);
	}
}
