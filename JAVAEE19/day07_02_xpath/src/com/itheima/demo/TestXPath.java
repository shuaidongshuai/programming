package com.itheima.demo;

import java.util.List;

import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.Node;
import org.dom4j.io.SAXReader;
import org.junit.Test;

public class TestXPath {
	@Test
	public void test1() throws Exception{
			SAXReader read = new SAXReader();
			Document document = read.read("src/Dom4jTest.xml");
			List nodes = document.selectNodes("/bookstore//book/title");
			for (int i = 0; i < nodes.size(); i++) {
				Node node = (Node) nodes.get(i);
				System.out.println(node.getText());
			}
	}
}
