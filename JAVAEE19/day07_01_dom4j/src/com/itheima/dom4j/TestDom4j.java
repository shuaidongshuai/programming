package com.itheima.dom4j;

import java.util.List;

import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.Element;
import org.dom4j.Node;
import org.dom4j.io.SAXReader;
import org.junit.Test;

public class TestDom4j {
	@Test// 1、得到某个具体的节点内容:第2本书的书名--》葵花宝典
	public void test1() throws DocumentException{
		 SAXReader reader = new SAXReader();//创建一个xml解析对象
	     Document document = reader.read("src/Book.xml");//把xml文档加载到document对象中
	     Element root = document.getRootElement();
	    /* Element bookNode = root.element("书");
	     System.out.println(bookNode.getName());*/
	     List list = root.elements();//得到当前节点的所有子节点
	     Element secondBook = (Element) list.get(1);//得到第二本书对象
	     String name = secondBook.element("书名").getText();//得到当前节点的文本内容
	     System.out.println(name);
	}
	
	@Test // 2、遍历所有元素节点
	public void test2() throws DocumentException{
		SAXReader reader = new SAXReader();//创建一个xml解析对象
	     Document document = reader.read("src/Book.xml");//把xml文档加载到document对象中
	     Element root = document.getRootElement();
	     treeWalk(root);
	}

	private void treeWalk(Element ele) {
		System.out.println(ele.getName());//输出当前节点的名子
		for (int i = 0; i < ele.nodeCount(); i++) {//ele.nodeCount()得到当前节点的所有子节点的数量
			Node node = ele.node(i);//取出下标为i的节点 
			if(node instanceof Element){//判断当前节点是否为标签
				treeWalk((Element)node);//把node强转为标签(Element)
			}else{
				System.out.println(node.getText());
			}
		}
	}
	
}
