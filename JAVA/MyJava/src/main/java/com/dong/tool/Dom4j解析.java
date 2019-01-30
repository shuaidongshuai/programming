package com.dong.tool;

import org.dom4j.Document;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

import java.io.File;
import java.util.List;

public class Dom4j解析 {

    public static void main(String[] args) throws Exception {
        SAXReader reader = new SAXReader();
        File file = new File("/Users/com.dong/Documents/code/MyJava/src/main/resources/scene.xml");
        Document document = reader.read(file);
        Element root = document.getRootElement();
        List<Element> childElements = root.elements();
        for (Element child : childElements) {
            //未知属性名情况下
            //List<Attribute> attributeList = child.attributes();
            //for (Attribute attr : attributeList) {
            //    System.out.println(attr.getName() + ": " + attr.getValue());
            //}

            //已知属性名情况下
            System.out.println("name: " + child.attributeValue("name") + "\tdesc:" + child.attributeValue("desc"));

            //未知子元素名情况下
            //List<Element> elementList = child.elements();
            //for (Element ele : elementList) {
            //    System.out.println(ele.getName() + ": " + ele.getText());
            //}

            //已知子元素名的情况下
            //System.out.println("action:" + child.elementText("action"));

            List<Element> elements = child.elements();
            for(Element element : elements){
                String actionName = element.attributeValue("actionName");
                String aClass = element.attributeValue("class");
                String desc = element.attributeValue("desc");
                System.out.println(actionName + "\t" + aClass + "\t" + desc);
            }
            System.out.println();
        }
    }

}
