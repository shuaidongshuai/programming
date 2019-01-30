package com.dong.clearppclassinvoke;

import lombok.Getter;
import lombok.Setter;
import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

/**
 * @author com.dong
 */
public class ParseSceneXml {
    public static List<Scene> parseScene(String fileName) throws DocumentException {
        List<Scene> scenes = new ArrayList<>();

        SAXReader reader = new SAXReader();
        File file = new File(fileName);
        Document document = reader.read(file);
        Element root = document.getRootElement();
        List<Element> childElements = root.elements();
        for (Element child : childElements) {
            Scene scene = new Scene();
            scenes.add(scene);

            List<Action> actions = new ArrayList<>();
            scene.setName(child.attributeValue("name"));
            scene.setDesc(child.attributeValue("desc"));
            scene.setActions(actions);

            List<Element> elements = child.elements();
            for(Element element : elements){
                Action action = new Action();
                action.setName(element.attributeValue("actionName"));
                action.setClazz(element.attributeValue("class"));
                action.setDesc(element.attributeValue("desc"));
                actions.add(action);
            }
        }
        return  scenes;
    }
}

@Getter
@Setter
class Action{
    private String name;
    private String clazz;
    private String desc;
}

@Getter
@Setter
class Scene{
    private String name;
    private String desc;
    private List<Action> actions;
}