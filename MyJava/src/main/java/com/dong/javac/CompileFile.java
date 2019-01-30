package com.dong.javac;

import com.sun.source.tree.CompilationUnitTree;
import com.sun.source.tree.Tree;
import com.sun.source.util.JavacTask;
import com.sun.source.util.TreeScanner;
import com.sun.tools.javac.api.JavacTool;
import com.sun.tools.javac.file.JavacFileManager;
import com.sun.tools.javac.tree.JCTree;
import com.sun.tools.javac.util.Context;

import javax.tools.JavaFileObject;
import java.io.IOException;
import java.nio.charset.Charset;

/**
 * @author dong
 */
public class CompileFile {
    private static String path = "/Users/dong/Documents/code/MyJava/src/main/java/com/dong/guava/ListenableFutureTest.java";

    public static void main(String[] args) {
        compile();
    }

    static void compile(){
        Context context = new Context();
        JavacFileManager javacFileManager = new JavacFileManager(context, true, Charset.defaultCharset());
        Iterable<? extends JavaFileObject> javaFileObjects = javacFileManager.getJavaFileObjects(path);

        JavacTool javacTool = JavacTool.create();
        JavacTask task = javacTool.getTask(null, javacFileManager, null, null, null, javaFileObjects);

        try {
            Iterable<? extends CompilationUnitTree> parse = task.parse();
            for (CompilationUnitTree tree : parse) {
                Object accept = tree.accept(new SourceVisitor(), null);
                System.out.println(accept);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    static class SourceVisitor extends TreeScanner {
        @Override
        public Object scan(Tree node, Object o) {
            if (node != null) {
                System.out.println("kind=" + node.getKind() + "\tclass=" + node.getClass() + "\tnode=" + node + "\to=" + o);
                if (node.getKind() == Tree.Kind.CLASS) {
                    JCTree.JCClassDecl classDecl = (JCTree.JCClassDecl)node;
                    for (JCTree tree : classDecl.getMembers()) {

                    }
                }
            }
            return super.scan(node, o);
        }
    }
}
