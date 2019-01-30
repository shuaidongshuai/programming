package com.dong.javac;

import com.sun.tools.classfile.*;
import com.sun.tools.classfile.ConstantPool.CONSTANT_InterfaceMethodref_info;
import com.sun.tools.classfile.ConstantPool.CONSTANT_Methodref_info;
import com.sun.tools.classfile.ConstantPool.CONSTANT_NameAndType_info;
import com.sun.tools.classfile.ConstantPool.CPInfo;
import com.sun.tools.javap.JavapFileManager;
import com.sun.tools.javap.JavapTask;
import com.sun.tools.javap.JavapTask.ClassFileInfo;

import javax.tools.DiagnosticCollector;
import javax.tools.JavaFileManager;
import javax.tools.JavaFileObject;
import javax.tools.JavaFileObject.Kind;
import javax.tools.SimpleJavaFileObject;
import java.io.*;
import java.net.URI;
import java.net.URISyntaxException;

/**
 * @author dong
 */
public class ParseClass {
    public static void main(String[] args) {
        DiagnosticCollector<JavaFileObject> dc = new DiagnosticCollector<JavaFileObject>();
        StringWriter sw = new StringWriter();
        PrintWriter pw = new PrintWriter(sw);
        JavaFileManager fm = JavapFileManager.create(dc, pw);

        URI fileUri = null;
        try {
            //fileUri = new URI("file:///Users/dong/Documents/cainiao/logistic-solution-platform/solution-domains/domain-order/target/classes/com/cainiao/lsp/domains/order/service/OrderDomainService.class");
            //fileUri = new URI("file:///Users/dong/Documents/cainiao/logistic-solution-platform/solution-logistic-services/target/classes/com/cainiao/lsp/logisticservice/pickup/ext/PickupExtFacade$2.class");
            fileUri = new URI("file:///Users/dong/Documents/code/MyJava/src/main/java/com/dong/test/ClassTest.class");
        } catch (URISyntaxException e) {
            e.printStackTrace();
        }

        JavaFileObject file = new MySimpleJavaFileObject(fileUri, Kind.CLASS);

        JavapTask javapTask = new JavapTask();
        try {
            ClassFileInfo read = javapTask.read(file);
            ConstantPool constant_pool = read.cf.constant_pool;
            BootstrapMethods_attribute bootstrapMethods = (BootstrapMethods_attribute)read.cf.getAttribute("BootstrapMethods");
            String lambdaName = null;
            String referenceMethodName = null;
            for (com.sun.tools.classfile.Method method : read.cf.methods) {
                Code_attribute code = (Code_attribute)method.attributes.get("Code");
                for (Instruction instruction : code.getInstructions()) {
                    Opcode opcode = instruction.getOpcode();
                    //invokedynamic指令
                    if(opcode == Opcode.INVOKEDYNAMIC){
                        int a = instruction.getShort(1);
                        ConstantPool.CONSTANT_InvokeDynamic_info constantInvokeDynamicInfo = (ConstantPool.CONSTANT_InvokeDynamic_info)constant_pool.get(a);
                        int bootstrapMethodAttrIndex = constantInvokeDynamicInfo.bootstrap_method_attr_index;
                        BootstrapMethods_attribute.BootstrapMethodSpecifier bootstrapMethodSpecifier = bootstrapMethods.bootstrap_method_specifiers[bootstrapMethodAttrIndex];
                        int bootstrapArgument = bootstrapMethodSpecifier.bootstrap_arguments[1];
                        ConstantPool.CONSTANT_MethodHandle_info constantMethodHandleInfo = (ConstantPool.CONSTANT_MethodHandle_info)constant_pool.get(bootstrapArgument);
                        int referenceIndex = constantMethodHandleInfo.reference_index;

                        ConstantPool.CPRefInfo cpRefInfo = null;
                        CPInfo cpInfo = constant_pool.get(referenceIndex);
                        if(cpInfo instanceof CONSTANT_InterfaceMethodref_info){
                            cpRefInfo = (CONSTANT_InterfaceMethodref_info)cpInfo;
                            CONSTANT_NameAndType_info nameAndTypeInfo = cpRefInfo.getNameAndTypeInfo();
                            referenceMethodName = nameAndTypeInfo.getName();
                            String className = cpRefInfo.getClassName();

                        } else if(cpInfo instanceof CONSTANT_Methodref_info) {
                            cpRefInfo = (CONSTANT_Methodref_info)cpInfo;
                            CONSTANT_NameAndType_info nameAndTypeInfo = cpRefInfo.getNameAndTypeInfo();
                            lambdaName = nameAndTypeInfo.getName();
                        } else {
                            System.out.println("error cpInfo");
                        }
                    }
                    //invokevirtual指令
                    if(opcode == Opcode.INVOKEVIRTUAL){
                        int a = instruction.getShort(1);
                        CPInfo cpInfo = constant_pool.get(a);
                        if (cpInfo instanceof CONSTANT_Methodref_info) {
                            CONSTANT_Methodref_info methodinfo = (CONSTANT_Methodref_info)cpInfo;

                            CONSTANT_NameAndType_info nameAndTypeInfo = methodinfo.getNameAndTypeInfo();
                            System.out.print(String.format("class:%s\tname:%s\ttype:%s", methodinfo.getClassName(), nameAndTypeInfo.getName(), nameAndTypeInfo.getType()));
                        } else if (cpInfo instanceof CONSTANT_InterfaceMethodref_info) {
                            CONSTANT_InterfaceMethodref_info interfaceMethodref_info = (CONSTANT_InterfaceMethodref_info)cpInfo;
                            CONSTANT_NameAndType_info nameAndTypeInfo = interfaceMethodref_info.getNameAndTypeInfo();
                            System.out.print(String.format("interface:%s,name:%s,type:%s", interfaceMethodref_info.getClassName(), nameAndTypeInfo.getName(), nameAndTypeInfo.getType()));
                        }
                        System.out.println();
                    }
                    if (opcode == Opcode.INVOKESTATIC
                        || opcode == Opcode.INVOKEVIRTUAL
                        || opcode == Opcode.INVOKESPECIAL
                        || opcode == Opcode.INVOKEINTERFACE
                        ) {
                        int a = instruction.getShort(1);
                        CPInfo cpInfo = constant_pool.get(a);
                        if (cpInfo instanceof CONSTANT_Methodref_info) {
                            CONSTANT_Methodref_info methodinfo = (CONSTANT_Methodref_info)cpInfo;
                            CONSTANT_NameAndType_info nameAndTypeInfo = methodinfo.getNameAndTypeInfo();
                            System.out.print(String.format("\tclass:%s,name:%s,type:%s\n", methodinfo.getClassName(), nameAndTypeInfo.getName(), nameAndTypeInfo.getType()));
                        } else if (cpInfo instanceof CONSTANT_InterfaceMethodref_info) {
                            CONSTANT_InterfaceMethodref_info interfaceMethodref_info = (CONSTANT_InterfaceMethodref_info)cpInfo;
                            CONSTANT_NameAndType_info nameAndTypeInfo = interfaceMethodref_info.getNameAndTypeInfo();
                            System.out.print(String.format("\tinterface:%s,name:%s,type:%s\n", interfaceMethodref_info.getClassName(), nameAndTypeInfo.getName(), nameAndTypeInfo.getType()));
                        }
                    }
                }
            }

            for(com.sun.tools.classfile.Method method : read.cf.methods){
                if(lambdaName != null && method.getName(constant_pool).equals(lambdaName)){
                    System.out.println(lambdaName);
                }
            }

            System.out.println(read);
        } catch (Exception e) {
        }
    }

    static class MySimpleJavaFileObject extends SimpleJavaFileObject {
        /**
         * Construct a SimpleJavaFileObject of the given kind and with the given URI.
         *
         * @param uri  the URI for this file object
         * @param kind the kind of this file object
         */
        protected MySimpleJavaFileObject(URI uri, Kind kind) {
            super(uri, kind);
        }

        @Override
        public InputStream openInputStream() throws IOException {
            return new FileInputStream(this.uri.toURL().getFile());
            //return super.openInputStream();
        }
    }
}
