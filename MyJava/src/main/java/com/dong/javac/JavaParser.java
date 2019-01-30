package com.dong.javac;

import com.dong.tool.FindAllFileUnderDirectory;
import com.sun.source.util.JavacTask;
import com.sun.source.util.TreeScanner;
import com.sun.tools.javac.api.JavacTool;
import com.sun.tools.javac.file.JavacFileManager;
import com.sun.tools.javac.util.Context;
import org.junit.Test;
import sun.reflect.generics.tree.Tree;

import javax.tools.JavaCompiler;
import javax.tools.JavaFileObject;
import java.io.IOException;
import java.nio.charset.Charset;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

/**
 * @author dong
 */
public class JavaParser{
    //private static final String path = "/Users/dong/Documents/code/MyJava/src/main/java/com/dong/guava/ListenableFutureTest.java";
    //private static String path = "/Users/dong/Documents/code/MyJava/src/main/java/com/dong/base/CompletableFutureTest.java";
    private static String path = "/Users/dong/Documents/code/MyJava/src/main/java/com/dong/test/Base.java";
    private static String pathRoot = "/Users/dong/Documents/code/MyJava";

    private JavacFileManager fileManager;
    private JavacTool javacTool;

    public JavaParser() {
        Context context = new Context();
        fileManager = new JavacFileManager(context, true, Charset.defaultCharset());
        javacTool = JavacTool.create();
    }

    public void parseJavaFiles(String path) throws IOException {
        Iterable<? extends JavaFileObject> files = fileManager.getJavaFileObjects(path);
        //解析java文件
        JavaCompiler.CompilationTask compilationTask = javacTool.getTask(null, fileManager, null, null, null, files);
        JavacTask javacTask = (JavacTask) compilationTask;
        Iterable<? extends CompilationUnitTree> result = javacTask.parse();
        SourceVisitor sourceVisitor = new SourceVisitor();
        for (CompilationUnitTree tree : result) {
            tree.accept(sourceVisitor, null);
        }

        //ParseSourceVisitor(sourceVisitor);
        List<String> possibleFullMethod = getPossibleFullMethod(sourceVisitor);
        for (String method : possibleFullMethod) {
            System.out.println(method);
        }
    }


    public List<String> getPossibleFullMethod(SourceVisitor sourceVisitor){
        String currentPackageName = sourceVisitor.currentPackageName;
        List<String> methods = sourceVisitor.methods;
        List<String> methodsInvocation = sourceVisitor.methodsInvocation;
        List<String> imports = sourceVisitor.imports;
        List<String> clazzs = sourceVisitor.clazzs;
        HashMap<String, List<String>> variables = sourceVisitor.variables;

        //区分带*的import
        List<String> importLike = new ArrayList<>();
        List<String> importSelf = new ArrayList<>();
        for(String imp : imports){
            if('*' == imp.charAt(imp.length() - 1)){
                importLike.add(imp.substring(0, imp.length() - 2));
            } else{
                importSelf.add(imp);
            }
        }

        //类名->方法(可能含有多个方法 . 来分割)
        List<String> res = new ArrayList<>();
        for(String methodInvocation : methodsInvocation){
            //找到除本类的以外的调用
            //查找这次调用形式（1.func 2.var.func 3.var.func.func 4.Class.func 5.Class.func.func）
            List<String> keyVal = splitOnePoint(methodInvocation);
            //只有>1才有可能调用外部类
            if(keyVal.size() > 1){
                List<String> clazzNames = new ArrayList<>();
                String clazzName = keyVal.get(0);
                //检查是否为某个变量
                if(variables.containsKey(clazzName)){
                    List<String> types = variables.get(clazzName);
                    for(String type : types){
                        //去掉泛型
                        String simpleType = delGenerics(type);
                        clazzNames.add(simpleType);
                    }
                } else{
                    clazzNames.add(clazzName);
                }
                for(String cn : clazzNames){
                    //由于一个文件可能包含多个class所以>1也有可能是内部的类
                    boolean isLocalClazz = false;
                    for(String clazz : clazzs){
                        if(cn.equals(clazz)){
                            isLocalClazz = true;
                        }
                    }
                    if(isLocalClazz){
                        continue;
                    }
                    //和头文件组合
                    boolean isLike = true;
                    for(String imp : importSelf){
                        String lastString = getLastString(imp, ".");
                        if(lastString.equals(cn)){
                            cn = imp;
                            isLike = false;
                        }
                    }
                    if(isLike){
                        for(String imp : importLike){
                            res.add(imp + "." + cn);
                        }
                        //还要添加同一个包下面的
                        res.add(currentPackageName + "." + cn);
                    } else {
                        res.add(cn);
                    }
                }
            }
        }
        return res;
    }

    public String delGenerics(String str){
        int len = str.length();
        for(int i = 0; i < len; ++i){
            if(str.charAt(i) == '<'){
                return str.substring(0, i);
            }
        }
        return new String(str);
    }

    public String getLastString(String str, String splitPoint){
        if(str == null){
            return "";
        }
        int idx = str.length();
        while(--idx >= 0){
            if(splitPoint.equals(str.charAt(idx))){
                return str.substring(idx);
            }
        }
        return "";
    }

    public List<String> splitOnePoint(String str){
        List<String> res = new ArrayList<>();
        if(str == null){
            return res;
        }
        int size = str.length();
        int splitPoint = -1;
        while(++splitPoint < size){
            if('.' == str.charAt(splitPoint)){
                break;
            }
        }
        res.add(str.substring(0, splitPoint));
        if(splitPoint + 1 < size){
            res.add(str.substring(splitPoint + 1));
        }
        return res;
    }

    static class SourceVisitor extends TreeScanner<Void, Void> {
        private String currentPackageName = null;
        private List<String> imports = new ArrayList<>();
        private List<String> methods = new ArrayList<>();
        private List<String> methodsInvocation = new ArrayList<>();
        private List<String> clazzs = new ArrayList<>();

        private HashMap<String, List<String>> variables = new HashMap<>();

        @Override
        public Void scan(Tree node, Void aVoid) {
            if(currentPackageName == null){
                currentPackageName = node.toString();
            }
            return super.scan(node, aVoid);
        }

        @Override
        public Void visitImport(ImportTree node, Void aVoid) {
            imports.add(node.getQualifiedIdentifier().toString());
            return super.visitImport(node, aVoid);
        }

        /**
         * 查看所有变量
         * @param node
         * @param aVoid
         * @return
         */
        @Override
        public Void visitVariable(VariableTree node, Void aVoid) {
            //type有可能为Null
            if(node.getType() != null){
                if(variables.containsKey(node.getName().toString())){
                    List<String> list = variables.get(node.getName().toString());
                    list.add(node.getType().toString());
                } else{
                    ArrayList<String> list = new ArrayList<>(1);
                    list.add(node.getType().toString());
                    variables.put(node.getName().toString(), list);
                }
            }
            return super.visitVariable(node, aVoid);
        }

        /**
         * 查看所有类
         * @param node
         * @param aVoid
         * @return
         */
        @Override
        public Void visitClass(ClassTree node, Void aVoid) {
            //formatPtrln("class name: %s", node.getSimpleName());
            //List<? extends Tree> members = node.getMembers();
            //for(Tree member : members){
            //    System.out.println(member);
            //}
            //再遍历所有方法
            //for (Tree member : node.getMembers()) {
            //    if (member instanceof VariableTree) {
            //        VariableTree variable = (VariableTree) member;
            //        List<? extends AnnotationTree> annotations = variable.getModifiers().getAnnotations();
            //        if (annotations.size() > 0) {
            //            formatPtrln("variable: %s, annotaion: %s", variable.getName(), annotations.get(0).getAnnotationType());
            //        } else {
            //            formatPtrln("variable: %s", variable.getName());
            //        }
            //    }
            //}
            String clazz = node.getSimpleName().toString();
            if(!clazz.isEmpty()){
                clazzs.add(clazz);
            }
            return super.visitClass(node, aVoid);
        }

        /**
         * 所有方法（不包括lambda）
         * @param node
         * @param aVoid
         * @return
         */
        @Override
        public Void visitMethod(MethodTree node, Void aVoid) {
            methods.add(node.getName().toString());
            return super.visitMethod(node, aVoid);
        }

        /**
         * Lambda表达式
         * @param node
         * @param aVoid
         * @return
         */
        @Override
        public Void visitLambdaExpression(LambdaExpressionTree node, Void aVoid) {
            //System.out.println("Lambda：" + node);
            return super.visitLambdaExpression(node, aVoid);
        }

        /**
         * 所有被执行的方法
         * @param node
         * @param aVoid
         * @return
         */
        @Override
        public Void visitMethodInvocation(MethodInvocationTree node, Void aVoid) {
            //System.out.println("MethodInvocation:" + node);
            methodsInvocation.add(node.getMethodSelect().toString());
            return super.visitMethodInvocation(node, aVoid);
        }

        /**
         * 注解
         * @param node
         * @param aVoid
         * @return
         */
        @Override
        public Void visitAnnotation(AnnotationTree node, Void aVoid) {
            //System.out.println("Annotation:" + node);
            return super.visitAnnotation(node, aVoid);
        }
    }

    public static void main(String[] args) throws IOException {
        //查找所有文件
        List<String> allFile = new FindAllFileUnderDirectory().findAllFile(pathRoot);
        //过滤所有非java文件
        List<String> javaFiles = allFile.stream().filter(file -> file.substring(file.length() - 5).equals(".java"))
            .collect(Collectors.toList());

        //找到所有文件
        for(String javaFile : javaFiles){
            System.out.println("-----------" + javaFile + "------------");
            new JavaParser().parseJavaFiles(javaFile);
        }
    }

    @Test
    public void parseSourceVisitor() throws IOException {
        Iterable<? extends JavaFileObject> files = fileManager.getJavaFileObjects(path);
        //解析java文件
        JavaCompiler.CompilationTask compilationTask = javacTool.getTask(null, fileManager, null, null, null, files);
        JavacTask javacTask = (JavacTask) compilationTask;
        Iterable<? extends CompilationUnitTree> result = javacTask.parse();
        SourceVisitor sourceVisitor = new SourceVisitor();

        for (CompilationUnitTree tree : result) {
            tree.accept(sourceVisitor, null);
        }
        List<String> methods = sourceVisitor.methods;
        List<String> methodsInvocation = sourceVisitor.methodsInvocation;
        List<String> imports = sourceVisitor.imports;
        List<String> clazzs = sourceVisitor.clazzs;
        HashMap<String, List<String>> variables = sourceVisitor.variables;

        for(String str : methods){
            System.out.println("method:\t" + str);
        }
        for(String str : methodsInvocation){
            System.out.println("methodsInvocation:\t" + str);
        }
        for(String str : imports){
            System.out.println("imports:\t" + str);
        }
        for(String str : clazzs){
            System.out.println("clazzs:\t" + str);
        }
        for(Map.Entry<String, List<String>> entry : variables.entrySet()){
            System.out.println("key:" + entry.getKey() + "\tvalue:" + entry.getValue());
        }
    }

    @Test
    public void test(){
        List<String> strings = splitOnePoint("hello.dong.nice");
        for(String str : strings){
            System.out.println(str);
        }
        strings = splitOnePoint("hello.");
        for(String str : strings){
            System.out.println(str);
        }
        strings = splitOnePoint("hello");
        for(String str : strings){
            System.out.println(str);
        }
    }
}