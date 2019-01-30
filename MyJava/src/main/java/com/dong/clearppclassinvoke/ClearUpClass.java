package com.dong.clearppclassinvoke;

import com.sun.tools.classfile.*;
import com.sun.tools.javap.JavapTask;

import javax.tools.JavaFileObject;
import javax.tools.SimpleJavaFileObject;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.URI;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * @author dong
 */
public class ClearUpClass {
    /**
     * class名->class路径
     */
    Map<String, String> classPathMap = new HashMap<>(1024);

    /**
     * class名->classNode
     */
    Map<String, ClassNode> classNodeMap = new HashMap<>(1024);

    /**
     * class名.method名.parameterTypes->methodNode
     */
    Map<String, MethodNode> methodNodeMap = new HashMap<>(4096);

    /**
     * class名.method名->class名.method名.parameterTypes列表
     */
    Map<String, List<String>> classMethodParameterMap = new HashMap<>(1024);

    /**
     * 梳理出来的扩展点链
     */
    List<List<String>> allExtensionLink = new ArrayList<>();

    public ClearUpClass() {
    }

    public String buildClassMethodParamName(String className, String methodName, String parameterTypes) {
        return className + "." + methodName + "." + parameterTypes;
    }

    public String buildClassMethodName(String className, String methodName) {
        return className + "." + methodName;
    }

    private List<String> findAllClassPath(String projectPath) {
        List<String> filesPath = new ArrayList<>();
        File rootFile = new File(projectPath);
        if (!rootFile.exists() || !rootFile.isDirectory()) {
            return null;
        }
        List<File> directorys = new ArrayList<>();
        directorys.add(rootFile);
        int idx = -1;
        while (++idx < directorys.size()) {
            File directory = directorys.get(idx);
            File[] listFiles = directory.listFiles();
            for (File file : listFiles) {
                if (file.isDirectory()) {
                    directorys.add(file);
                } else {
                    filesPath.add(file.getAbsolutePath());
                }
            }
        }
        return filesPath;
    }

    private Map<String, String> getClassPathMap(String projectPath) {
        //检查是否是.class文件 并取出class名
        String regex = ".*target/classes/(.*)\\.class";
        Pattern pattern = Pattern.compile(regex);
        List<String> allClassPath = findAllClassPath(projectPath);
        for (String classPath : allClassPath) {
            Matcher matcher = pattern.matcher(classPath);
            while (matcher.find()) {
                String className = matcher.group(1);
                classPathMap.put(className, classPath);
            }
        }
        return classPathMap;
    }

    private ClassNode loadClass(String classPath) throws Exception {
        ClassNode classNode = new ClassNode();

        classPath = "file://" + classPath;
        URI fileUri = new URI(classPath);

        JavaFileObject file = new MySimpleJavaFileObject(fileUri, JavaFileObject.Kind.CLASS);
        JavapTask javapTask = new JavapTask();
        JavapTask.ClassFileInfo read = javapTask.read(file);

        classNode.setClassName(read.cf.getName());
        classNode.setSuperName(read.cf.getSuperclassName());
        classNode.setFields(read.cf.fields);
        classNode.setConstantPool(read.cf.constant_pool);

        List<MethodNode> methodNodes = new ArrayList<>();
        classNode.setMethodNodes(methodNodes);

        /**
         * 遍历方法
         */
        ConstantPool constantPool = read.cf.constant_pool;
        for (Method method : read.cf.methods) {
            Descriptor descriptor = method.descriptor;

            MethodNode methodNode = new MethodNode();
            methodNodes.add(methodNode);

            String regex = "(\\(.*\\))(.*)";
            Pattern pattern = Pattern.compile(regex);
            Matcher matcher = pattern.matcher(descriptor.getValue(constantPool));
            while (matcher.find()) {
                methodNode.setParameterTypes(matcher.group(1));
                methodNode.setRet(matcher.group(2));
            }
            methodNode.setClassName(classNode.getClassName());
            methodNode.setSuperClassName(classNode.getSuperName());
            methodNode.setMethodName(method.getName(constantPool));

            List<CallMethod> callMethods = new ArrayList<>();
            methodNode.setCallMethods(callMethods);

            Code_attribute code = (Code_attribute)method.attributes.get("Code");
            if (code == null) {
                continue;
            }
            for (Instruction instruction : code.getInstructions()) {
                Opcode opcode = instruction.getOpcode();
                if (opcode == Opcode.INVOKEVIRTUAL || opcode == Opcode.INVOKESTATIC
                    || opcode == Opcode.INVOKESPECIAL || opcode == Opcode.INVOKEINTERFACE) {
                    int a = instruction.getShort(1);
                    ConstantPool.CPInfo cpInfo = constantPool.get(a);
                    if (cpInfo instanceof ConstantPool.CONSTANT_Methodref_info
                        || cpInfo instanceof ConstantPool.CONSTANT_InterfaceMethodref_info) {
                        ConstantPool.CPRefInfo cpRefInfo = (ConstantPool.CPRefInfo)cpInfo;
                        ConstantPool.CONSTANT_NameAndType_info nameAndTypeInfo = cpRefInfo.getNameAndTypeInfo();

                        CallMethod callMethod = new CallMethod();
                        callMethods.add(callMethod);

                        //切分出类型和返回值
                        String typesRet = nameAndTypeInfo.getType();
                        matcher = pattern.matcher(typesRet);
                        while (matcher.find()) {
                            callMethod.setParameterTypes(matcher.group(1));
                            callMethod.setRet(matcher.group(2));
                        }
                        callMethod.setMethodName(nameAndTypeInfo.getName());
                        callMethod.setClassName(cpRefInfo.getClassName());
                    }
                }
            }
        }
        return classNode;
    }

    /**
     * 加载项目中所有class
     *
     * @param projectPath
     * @return
     */
    public void loadAllClass(String projectPath) throws Exception {
        getClassPathMap(projectPath);
        for (String classPath : classPathMap.values()) {
            //加载class
            ClassNode classNode = loadClass(classPath);
            for (MethodNode methodNode : classNode.getMethodNodes()) {
                String className = methodNode.getClassName();
                String methodName = methodNode.getMethodName();
                String parameterTypes = methodNode.getParameterTypes();

                String key = buildClassMethodName(className, methodName);
                String value = buildClassMethodParamName(className, methodName, parameterTypes);
                List<String> mapValue = classMethodParameterMap.get(key);
                //处理类名方法名相同，参数不同情况
                if (mapValue == null) {
                    mapValue = new ArrayList<>();
                    mapValue.add(value);
                    classMethodParameterMap.put(key, mapValue);
                } else {
                    mapValue.add(value);
                }
                //放入方法节点map里面
                methodNodeMap.put(value, methodNode);
            }
            classNodeMap.put(classNode.getClassName(), classNode);
        }
    }

    public boolean haveNodeInLink(MethodNode linkNode, MethodNode curNode) {
        while (linkNode != null) {
            if (linkNode.equals(curNode)) {
                return true;
            }
            linkNode = methodNodeMap.get(
                buildClassMethodParamName(linkNode.getSuperClassName(), linkNode.getMethodName(),
                    linkNode.getParameterTypes()));
        }
        return false;
    }

    public MethodNode run(String className, String methodName, String parameterTypes) {
        if (className.equals("com/cainiao/lsp/domains/order/executor/OrderValidator") && methodName.equals(
            "lambda$validate$0") && parameterTypes.equals("(Lcom/cainiao/lsp/domains/order/model/ValidateOrder;)")) {
            System.out.println("dong");
        }
        String classMethodParamName = buildClassMethodParamName(className, methodName, parameterTypes);
        MethodNode methodNode = methodNodeMap.get(classMethodParamName);
        if (methodNode == null) {
            ClassNode classNode = classNodeMap.get(className);
            if (classNode == null) {
                //说明这次调用不在本项目
                methodNode = new MethodNode();
                methodNode.setClassName(className);
                methodNode.setMethodName(methodName);
                methodNode.setParameterTypes(parameterTypes);
                return methodNode;
            }
            String superClassName = classNode.getSuperName();
            //有可能在父类中
            methodNode = run(superClassName, methodName, parameterTypes);
            return methodNode;
        }

        //如果已有子方法节点，说明之前被别的方法遍历过，此时不需要遍历
        if (methodNode.getMethodNodes() != null) {
            return methodNode;
        }

        List<MethodNode> childMethodNodes = new ArrayList<>();
        methodNode.setMethodNodes(childMethodNodes);
        //递归遍历方法中被调用的方法
        List<CallMethod> callMethods = methodNode.getCallMethods();
        for (CallMethod callMethod : callMethods) {
            String cn = callMethod.getClassName();
            String mn = callMethod.getMethodName();
            String pt = callMethod.getParameterTypes();
            //防止项目中递归调用
            if (haveNodeInLink(methodNode, new MethodNode(cn, mn, pt))) {
                continue;
            }
            MethodNode childMethodNode = run(cn, mn, pt);
            if (childMethodNode != null) {
                childMethodNodes.add(childMethodNode);
            }
        }
        return methodNode;
    }

    public MethodNode clearUpMethodWithParam(String className, String methodName, String parameterTypes) {
        MethodNode methodNode = run(className, methodName, parameterTypes);
        return methodNode;
    }

    public List<MethodNode> clearUpMethod(String className, String methodName) {
        List<MethodNode> methodNodes = new ArrayList<>();
        List<String> classMethodParamNames = classMethodParameterMap.get(buildClassMethodName(className, methodName));
        for (String classMethodParamName : classMethodParamNames) {
            String[] split = classMethodParamName.split("\\.");
            if (split.length != 3) {
                System.out.println("error classMethodParamName:" + classMethodParamName);
            }
            MethodNode methodNode = clearUpMethodWithParam(className, methodName, split[2]);
            if (methodName != null) {
                methodNodes.add(methodNode);
            }
        }
        return methodNodes;
    }

    /**
     * 不带参数遍历
     *
     * @param projectPath
     * @param xmlPath
     * @param methodName
     * @return
     * @throws Exception
     */
    public Map<String, Map<String, List<MethodNode>>> getMethodTree(String projectPath, String xmlPath,
                                                                    String methodName)
        throws Exception {
        //加载所有class到内存
        loadAllClass(projectPath);

        //加载scene.xml
        List<Scene> scenes = ParseSceneXml.parseScene(xmlPath);

        //遍历每个入口
        Map<String, Map<String, List<MethodNode>>> sceneRootsMap = new HashMap<>(128);
        for (Scene scene : scenes) {
            Map<String, List<MethodNode>> roots = new HashMap<>(64);
            sceneRootsMap.put(scene.getDesc(), roots);
            for (Action action : scene.getActions()) {
                String className = action.getClazz().replaceAll("\\.", "/");
                List<MethodNode> rootList = clearUpMethod(className, methodName);
                roots.put(action.getDesc(), rootList);
            }
        }
        return sceneRootsMap;
    }

    /**
     * 带参数遍历
     *
     * @param projectPath
     * @param xmlPath
     * @param methodName
     * @param parameterTypes
     * @return
     * @throws Exception
     */
    public Map<String, Map<String, MethodNode>> getMethodTree(String projectPath, String xmlPath, String methodName,
                                                              String parameterTypes)
        throws Exception {
        //加载所有class到内存
        loadAllClass(projectPath);

        //加载scene.xml
        List<Scene> scenes = ParseSceneXml.parseScene(xmlPath);

        //遍历每个入口
        Map<String, Map<String, MethodNode>> sceneRootsMap = new HashMap<>(238);
        for (Scene scene : scenes) {
            Map<String, MethodNode> roots = new HashMap<>(64);
            sceneRootsMap.put(scene.getDesc(), roots);
            for (Action action : scene.getActions()) {
                String className = action.getClazz().replaceAll("\\.", "/");
                MethodNode rootList = clearUpMethodWithParam(className, methodName, parameterTypes);
                roots.put(action.getDesc(), rootList);
            }
        }
        return sceneRootsMap;
    }

    public boolean checkExtensionPoint(MethodNode node) {
        if (node.getClassName().equals("com/cainiao/gle/extension/ExtensionExecutor")) {
            return true;
        }
        return false;
    }

    public CallMethod parseReferenceMethod(ConstantPool.CONSTANT_InterfaceMethodref_info constantInterfaceMethodrefInfo)
        throws ConstantPoolException {
        CallMethod res = new CallMethod();
        ConstantPool.CONSTANT_NameAndType_info nameAndTypeInfo = constantInterfaceMethodrefInfo.getNameAndTypeInfo();
        res.setClassName(constantInterfaceMethodrefInfo.getClassName());
        res.setMethodName(nameAndTypeInfo.getName());
        res.setParameterTypes(nameAndTypeInfo.getType());
        return res;
    }

    public List<CallMethod> parseLambdaMethod(ConstantPool.CONSTANT_Methodref_info constantMethodrefInfo)
        throws ConstantPoolException {
        String className = constantMethodrefInfo.getClassName();
        ConstantPool.CONSTANT_NameAndType_info nameAndTypeInfo = constantMethodrefInfo.getNameAndTypeInfo();
        String lambdaMethodName = nameAndTypeInfo.getName();
        String typesRet = nameAndTypeInfo.getType();

        String regex = "(\\(.*\\))(.*)";
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(typesRet);
        String types = null;
        while (matcher.find()) {
            types = matcher.group(1);
        }
        MethodNode methodNode = methodNodeMap.get(buildClassMethodParamName(className, lambdaMethodName, types));
        //由于这个扩展点方法没有被调用过，所以只有callMethods中有这个扩展点方法
        List<CallMethod> res = methodNode.getCallMethods();
        return res;
    }

    public List<CallMethod> parseExtensionPoint(MethodNode preNode, MethodNode curNode) throws Exception {
        List<CallMethod> callMethods = new ArrayList<>();
        String classPath = classPathMap.get(preNode.getClassName());
        if (classPath == null) {
            System.out.println("Error classPath:" + classPath);
            return null;
        }
        classPath = "file://" + classPath;
        URI fileUri = new URI(classPath);

        JavaFileObject file = new MySimpleJavaFileObject(fileUri, JavaFileObject.Kind.CLASS);
        JavapTask javapTask = new JavapTask();
        JavapTask.ClassFileInfo read = javapTask.read(file);
        ConstantPool constantPool = read.cf.constant_pool;
        Method[] methods = read.cf.methods;
        BootstrapMethods_attribute bootstrapMethods = (BootstrapMethods_attribute)read.cf.getAttribute(
            "BootstrapMethods");
        MethodNode checkNode = new MethodNode();
        checkNode.setClassName("com/cainiao/gle/extension/ExtensionExecutor");
        for (Method method : methods) {
            //找到这个方法
            if (preNode.getMethodName().equals("getOrderCloseStrategy")) {
                System.out.println("dong");
            }
            Code_attribute code = (Code_attribute)method.attributes.get("Code");
            if (!preNode.getMethodName().equals(method.getName(constantPool)) || code == null) {
                continue;
            }
            //遍历指令
            int invokeDynamicLatest = -1;
            for (Instruction instruction : code.getInstructions()) {
                Opcode opcode = instruction.getOpcode();
                if (opcode == Opcode.INVOKEDYNAMIC) {
                    invokeDynamicLatest = instruction.getShort(1);
                }
                if (opcode == Opcode.INVOKEVIRTUAL || opcode == Opcode.INVOKESTATIC
                    || opcode == Opcode.INVOKESPECIAL || opcode == Opcode.INVOKEINTERFACE) {
                    int a = instruction.getShort(1);
                    ConstantPool.CPInfo cpInfo = constantPool.get(a);
                    if (cpInfo instanceof ConstantPool.CONSTANT_Methodref_info) {
                        ConstantPool.CONSTANT_Methodref_info methodrefInfo
                            = (ConstantPool.CONSTANT_Methodref_info)cpInfo;
                        if(!checkExtensionPoint(checkNode)){
                            continue;
                        }
                        //判断是否是调用扩展点的方法
                        if (curNode.getMethodName().equals(methodrefInfo.getNameAndTypeInfo().getName())) {
                            //开始解析扩展点方法
                            if (-1 == invokeDynamicLatest) {
                                System.out.println("error invokeDynamicLatest");
                                continue;
                            }
                            ConstantPool.CONSTANT_InvokeDynamic_info constantInvokeDynamicInfo
                                = (ConstantPool.CONSTANT_InvokeDynamic_info)constantPool.get(invokeDynamicLatest);
                            int bootstrapMethodAttrIndex
                                = constantInvokeDynamicInfo.bootstrap_method_attr_index;
                            BootstrapMethods_attribute.BootstrapMethodSpecifier bootstrapMethodSpecifier
                                = bootstrapMethods.bootstrap_method_specifiers[bootstrapMethodAttrIndex];
                            int bootstrapArgument = bootstrapMethodSpecifier.bootstrap_arguments[1];
                            ConstantPool.CONSTANT_MethodHandle_info constantMethodHandleInfo
                                = (ConstantPool.CONSTANT_MethodHandle_info)constantPool.get(bootstrapArgument);
                            int referenceIndex = constantMethodHandleInfo.reference_index;

                            cpInfo = constantPool.get(referenceIndex);
                            if (cpInfo instanceof ConstantPool.CONSTANT_InterfaceMethodref_info) {
                                //传递的是方法引用
                                CallMethod callMethod = parseReferenceMethod(
                                    (ConstantPool.CONSTANT_InterfaceMethodref_info)cpInfo);
                                callMethods.add(callMethod);
                                invokeDynamicLatest = -1;
                            } else if (cpInfo instanceof ConstantPool.CONSTANT_Methodref_info) {
                                //传递的是lambda
                                return parseLambdaMethod((ConstantPool.CONSTANT_Methodref_info)cpInfo);
                            } else {
                                System.out.println("error cpInfo");
                            }
                        }
                    }
                }
            }
        }
        return callMethods;
    }

    public void findExtensionPoint(List<String> methodList, MethodNode preNode, MethodNode curNode) throws Exception {
        if (preNode != null && preNode.getClassName().equals("com/cainiao/lsp/domains/order/executor/OrderValidator")
            && preNode.getMethodName().equals("validate")) {
            System.out.println("dong");
        }

        methodList.add(buildClassMethodName(curNode.getClassName(), curNode.getMethodName()));
        List<MethodNode> methodNodes = curNode.getMethodNodes();
        if (methodNodes != null) {
            for (MethodNode methodNode : methodNodes) {
                findExtensionPoint(methodList, curNode, methodNode);
            }
        }
        if (checkExtensionPoint(curNode)) {
            List<String> extensionLink = new LinkedList<>();
            allExtensionLink.add(extensionLink);
            extensionLink.addAll(methodList);
            //找到扩展点
            List<CallMethod> extensionmethods = parseExtensionPoint(preNode, curNode);
            if (extensionmethods != null) {
                for (CallMethod callMethod : extensionmethods) {
                    extensionLink.add(buildClassMethodName(callMethod.getClassName(), callMethod.getMethodName()));
                }
            } else {
                System.out.println("没找到扩展点");
            }
        }
        methodList.remove(methodList.size() - 1);
    }

    public List<List<String>> getExtensionPoint(String projectPath, String xmlPath, String methodName,
                                                String parameterTypes) throws Exception {
        Map<String, Map<String, MethodNode>> sceneRootsMap = getMethodTree(projectPath, xmlPath, methodName,
            parameterTypes);
        List<String> temp = new ArrayList<>();
        int curIdx = 0;
        for (Map.Entry<String, Map<String, MethodNode>> sceneRoot : sceneRootsMap.entrySet()) {
            for (Map.Entry<String, MethodNode> actionRoot : sceneRoot.getValue().entrySet()) {
                findExtensionPoint(temp, null, actionRoot.getValue());
                int size = allExtensionLink.size();
                while (curIdx < size) {
                    List<String> extensionLink = allExtensionLink.get(curIdx++);
                    extensionLink.add(0, actionRoot.getKey());
                    extensionLink.add(0, sceneRoot.getKey());
                }
            }
        }
        return allExtensionLink;
    }

    public void printMethodNode(MethodNode methodNode, int curDepth) {
        for (int i = 0; i < curDepth; i++) {
            System.out.print("\t");
        }
        System.out.println(buildClassMethodName(methodNode.getClassName(), methodNode.getMethodName()));
        List<MethodNode> methodNodes = methodNode.getMethodNodes();
        if (methodNodes != null) {
            for (MethodNode mn : methodNodes) {
                printMethodNode(mn, curDepth + 1);
            }
        }
    }

    public void printClassInvkeLink(Map<String, Map<String, MethodNode>> sceneRootsMap) {
        for (Map.Entry<String, Map<String, MethodNode>> sceneRoot : sceneRootsMap.entrySet()) {
            for (Map.Entry<String, MethodNode> actionRoot : sceneRoot.getValue().entrySet()) {
                System.out.println();
                System.out.println(sceneRoot.getKey() + "->" + actionRoot.getKey());
                printMethodNode(actionRoot.getValue(), 0);
            }
        }
    }

    public static void main(String[] args) throws Exception {
        ClearUpClass clearUpClass = new ClearUpClass();
        //Map<String, Map<String, List<MethodNode>>> sceneRootsMap = clearUpClass.getMethodTree(
        //    "/Users/dong/Documents/cainiao/logistic-solution-platform/",
        //    "/Users/dong/Documents/code/MyJava/src/main/resources/scene.xml", "execute");

        //Map<String, Map<String, MethodNode>> sceneRootsMap = clearUpClass.getMethodTree(
        //    "/Users/dong/Documents/cainiao/logistic-solution-platform/",
        //    "/Users/dong/Documents/code/MyJava/src/main/resources/scene.xml", "execute",
        //    "(Ljava/lang/Object;Ljava/lang/Object;)");
        //clearUpClass.printClassInvkeLink(sceneRootsMap);
        clearUpClass.getExtensionPoint("/Users/dong/Documents/cainiao/logistic-solution-platform/",
            "/Users/dong/Documents/code/MyJava/src/main/resources/scene.xml", "execute",
            "(Ljava/lang/Object;Ljava/lang/Object;)");
    }
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