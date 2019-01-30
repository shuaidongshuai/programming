package com.dong.javac;

import com.dong.tool.FindAllFileUnderDirectory;
import com.sun.tools.classfile.*;
import com.sun.tools.javap.JavapTask;
import lombok.Data;
import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;
import org.junit.Test;

import javax.tools.JavaFileObject;
import javax.tools.SimpleJavaFileObject;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.URI;
import java.net.URISyntaxException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

@Data
class ClassNode {
    private String className;
    private String usedMethodName;
    private List<SimpleMethod> callMethods;
    private List<ClassNode> classNodes;
    private ClassNode superNode;

    //public void copy(ClassNode cn){
    //    className = cn.className;
    //    usedMethodName = cn.usedMethodName;
    //    callMethods = cn.callMethods;
    //    //classNodes = cn.classNodes;
    //}

    public ClassNode findFather(ClassNode cn){
        ClassNode father = this.superNode;
        while(father != null){
            if(father.className.equals(cn.className) && father.usedMethodName.equals(cn.usedMethodName)){
                break;
            }
            father = father.superNode;
        }
        return father;
    }

    @Override
    public String toString() {
        return "ClassNode{" +
            "className='" + className + '\'' +
            ", usedMethodName='" + usedMethodName + '\'' +
            ", callMethods=" + callMethods +
            ", classNodes=" + classNodes +
            '}';
    }
}

@Data
class SimpleMethod {
    private String className;
    private String name;
    private List<String> type;
    private String ret;
}

@Data
class Action{
    private String name;
    private String clazz;
    private String desc;
}

@Data
class Scene{
    private String name;
    private String desc;
    private List<Action> actions;
}

class ParseXml{
    public List<Scene> ParseScene(String fileName) throws DocumentException {
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

public class 整理类关系 {
    public Map<String, String> classPathMap;
    /**
     * 主要用于防止递归
     */
    public Map<String, ClassNode> classNodeMap;

    //private ClassNode root;

    整理类关系() {
        classPathMap = createClassPathMap();
        classNodeMap = new HashMap<>(1024);
        //root = new ClassNode();
        //root.setClassNodes(new ArrayList<>());
    }

    public void run(ClassNode classNode, String className, String callName)
        throws URISyntaxException, ConstantPoolException, IOException, Descriptor.InvalidDescriptor {
        //防止递归
        //ClassNode haveNode = classNodeMap.get(className + "." + callName);
        //if(haveNode != null){
        //    classNode.copy(haveNode);
        //    return;
        //}
        ClassNode curNode = new ClassNode();
        curNode.setClassName(className);
        curNode.setUsedMethodName(callName);
        if(classNode.findFather(curNode) != null){
            return;
        }

        List<SimpleMethod> simpleMethods = new ArrayList<>();
        boolean isCallCurClass = false;

        //跳出递归
        String classPath = classPathMap.get(className);
        if(classPath == null){
            classNode.setClassName(className);
            classNode.setUsedMethodName(callName);
            return;
        }
        classPath = "file://" + classPath;
        URI fileUri = new URI(classPath);

        JavaFileObject file = new MySimpleJavaFileObject(fileUri, JavaFileObject.Kind.CLASS);
        JavapTask javapTask = new JavapTask();
        JavapTask.ClassFileInfo read = javapTask.read(file);

        //查找本类的方法
        ConstantPool constant_pool = read.cf.constant_pool;
        for (Method method : read.cf.methods) {
            Descriptor descriptor = method.descriptor;
            String parameterTypes = descriptor.getParameterTypes(constant_pool);
            String returnType = descriptor.getReturnType(constant_pool);

            //System.out.println(String.format("%s\t%s\t%s", method.descriptor.getReturnType(constant_pool), method.getName(constant_pool), method.descriptor.getParameterTypes(constant_pool)));
            //暂时只匹配方法名
            if (method.getName(constant_pool).equals(callName)) {
                isCallCurClass = true;
                Code_attribute code = (Code_attribute)method.attributes.get("Code");
                for (Instruction instruction : code.getInstructions()) {
                    if (instruction.getOpcode() == Opcode.INVOKEVIRTUAL) {
                        int a = instruction.getShort(1);
                        ConstantPool.CPInfo cpInfo = constant_pool.get(a);
                        if (cpInfo instanceof ConstantPool.CONSTANT_Methodref_info) {
                            ConstantPool.CONSTANT_Methodref_info methodinfo = (ConstantPool.CONSTANT_Methodref_info)cpInfo;
                            ConstantPool.CONSTANT_NameAndType_info nameAndTypeInfo = methodinfo.getNameAndTypeInfo();

                            //切分出类型和返回值
                            String typesRet = nameAndTypeInfo.getType();
                            String pattern = "^\\([A-Z]?(.*)\\)[A-Z]?(.*);?";
                            Pattern r = Pattern.compile(pattern);
                            Matcher m = r.matcher(typesRet);
                            while (m.find()) {
                                String types = m.group(1);
                                String ret = m.group(2);

                                List<String> typeList = new ArrayList<>();
                                String[] splitTypes = types.split(";");
                                for (String type : splitTypes) {
                                    typeList.add(type);
                                }

                                SimpleMethod simpleMethod = new SimpleMethod();
                                simpleMethod.setRet(ret);
                                simpleMethod.setName(nameAndTypeInfo.getName());
                                simpleMethod.setClassName(methodinfo.getClassName());
                                simpleMethod.setType(typeList);
                                
                                simpleMethods.add(simpleMethod);
                            }
                        }
                    }
                }
            }
        }
        //如果本类没有call方法，那么查看父类方法
        if(!isCallCurClass){
            String superclassName = read.cf.getSuperclassName();
            run(classNode, superclassName, callName);
            return;
        }

        //获取泛型
        if("com/cainiao/lsp/domains/order/service/OrderDomainService".equals(className)){
            Field[] fields = read.cf.fields;
            for(Field field : fields){
                Signature_attribute signature = (Signature_attribute)field.attributes.get("Signature");
                if(signature == null){
                    break;
                }
                Type.ClassType classType = (Type.ClassType)signature.getParsedSignature().getType(constant_pool);
                Type type = classType.typeArgs.get(0);
                System.out.println(classType.name + " 泛型:" + type);
            }
        }

        List<ClassNode> classNodes = new ArrayList<>();
        classNode.setClassName(className);
        classNode.setUsedMethodName(callName);
        classNode.setCallMethods(simpleMethods);
        classNode.setClassNodes(classNodes);
        //防止无限递归 放入map
        //classNodeMap.put(className + "." + callName, classNode);
        //递归调用
        for(SimpleMethod simpleMethod : classNode.getCallMethods()){
            ClassNode cn = new ClassNode();
            cn.setSuperNode(classNode);
            classNodes.add(cn);
            run(cn, simpleMethod.getClassName(), simpleMethod.getName());
        }
    }

    public void printClassNode(ClassNode classNode) {
        System.out.print(classNode.getClassName() + "." + classNode.getUsedMethodName() + " -> ");
        if (classNode.getClassNodes() == null) {
            System.out.println();
            return;
        }
        for (ClassNode cn : classNode.getClassNodes()) {
            printClassNode(cn);
        }
    }

    public Map<String, String> createClassPathMap(){
        Map<String, String> classPathMap = new HashMap<>(64);
        FindAllFileUnderDirectory findAllFileUnderDirectory = new FindAllFileUnderDirectory();
        List<String> allFilePath = findAllFileUnderDirectory.findAllFile(
            "/Users/dong/Documents/cainiao/logistic-solution-platform/");
        for(String str : allFilePath){
            String pattern = ".*target/classes/(.*)\\.class";
            Pattern r = Pattern.compile(pattern);
            Matcher m = r.matcher(str);
            while(m.find()){
                String className = m.group(1);
                classPathMap.put(className, str);
                //System.out.println(className + "\t" + str);
            }
        }
        return classPathMap;
    }

    public ClassNode findClassInvok(String className, String method)
        throws IOException, ConstantPoolException, URISyntaxException, Descriptor.InvalidDescriptor {
        ClassNode rootChild = new ClassNode();
        //root.getClassNodes().add(rootChild);
        run(rootChild, className, method);
        return rootChild;
    }

    class MySimpleJavaFileObject extends SimpleJavaFileObject {
        protected MySimpleJavaFileObject(URI uri, Kind kind) {
            super(uri, kind);
        }

        @Override
        public InputStream openInputStream() throws IOException {
            return new FileInputStream(this.uri.toURL().getFile());
        }
    }

    @Test
    public void test() throws Exception {
        findClassInvok("", "execute");
    }

    public static void main(String[] args) throws Exception {
        整理类关系 dong = new 整理类关系();
        Map<String, Map<String, ClassNode>> sceneRootsMap = new HashMap<>(128);
        ParseXml parseXml = new ParseXml();
        List<Scene> scenes = parseXml.ParseScene("/Users/dong/Documents/code/MyJava/src/main/resources/scene.xml");
        for(Scene scene : scenes){
            //System.out.println(scene.getName() + "\t" + scene.getDesc());
            Map<String, ClassNode> roots = new HashMap<>(32);
            sceneRootsMap.put(scene.getDesc(), roots);
            for(Action action : scene.getActions()){
                //System.out.println(action.getName() + "\t" + action.getClazz() + "\t" + action.getDesc());
                String classPath = action.getClazz().replaceAll("\\.", "/");
                ClassNode root = dong.findClassInvok(classPath, "execute");
                roots.put(action.getDesc(), root);
                //dong.printClassNode(root);
            }
            //System.out.println();
        }
        System.out.println(sceneRootsMap);
    }
}
