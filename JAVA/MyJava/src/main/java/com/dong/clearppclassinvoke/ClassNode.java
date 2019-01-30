package com.dong.clearppclassinvoke;

import com.sun.tools.classfile.ConstantPool;
import com.sun.tools.classfile.Field;
import lombok.Getter;
import lombok.Setter;

import java.util.List;

/**
 * @author com.dong
 */
@Getter
@Setter
public class ClassNode {
    private String className;
    private String superName;
    private Field[] fields;
    private List<MethodNode> methodNodes;
    private ConstantPool constantPool;
}
