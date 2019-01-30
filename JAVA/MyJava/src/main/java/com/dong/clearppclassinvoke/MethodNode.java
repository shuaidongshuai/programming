package com.dong.clearppclassinvoke;

import lombok.Getter;
import lombok.Setter;

import java.util.List;

/**
 * @author com.dong
 */
@Getter
@Setter
public class MethodNode {
    private String className;
    private String superClassName;
    private String methodName;
    private String parameterTypes;
    private String ret;
    private List<CallMethod> callMethods;
    private List<MethodNode> methodNodes;

    public MethodNode(){}

    public MethodNode(String className, String methodName, String parameterTypes){
        this.className = className;
        this.methodName = methodName;
        this.parameterTypes = parameterTypes;
    }

    @Override
    public boolean equals(Object obj) {
        if(obj != null && obj instanceof MethodNode){
            MethodNode methodNode = (MethodNode)obj;
            if(className.equals(methodNode.className) && methodName.equals(methodNode.methodName) && parameterTypes.equals(methodNode.parameterTypes)){
                return true;
            }
        }
        return false;
    }
}
