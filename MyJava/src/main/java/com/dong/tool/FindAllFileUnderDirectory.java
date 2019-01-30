package com.dong.tool;

import org.junit.Test;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

public class FindAllFileUnderDirectory {
    public String path = "/Users/dong/Documents/code/MyJava/src/main/java";
    public List<String> files = new ArrayList<>();

    @Test
    public void test(){
        //traverseFolder(path);
        findAllFile(path);
    }

    /**
     * 递归
     * 深度遍历
     * @param path
     */
    public List<String> traverseFolder(String path) {
        File rootFile = new File(path);
        if (rootFile.exists()) {
            File[] files = rootFile.listFiles();
            if (null == files || files.length == 0) {
                System.out.println("文件夹是空的!");
                return new ArrayList<>();
            } else {
                for (File file : files) {
                    if (file.isDirectory()) {
                        System.out.println("文件夹:" + file.getAbsolutePath());
                        traverseFolder(file.getAbsolutePath());
                    } else {
                        System.out.println("文件:" + file.getAbsolutePath());
                    }
                }
            }
        } else {
            System.out.println("文件不存在!");
        }
        return files;
    }

    /**
     * 非递归
     * 广度遍历
     */
    public List<String> findAllFile(String path){
        File rootFile = new File(path);
        if(!rootFile.exists() || !rootFile.isDirectory()){
            return null;
        }
        List<File> directorys = new ArrayList<>();
        directorys.add(rootFile);
        int idx = -1;
        while(++idx < directorys.size()){
            File file = directorys.get(idx);
            File[] listFiles = file.listFiles();
            for(File f : listFiles){
                if (f.isDirectory()) {
                    directorys.add(f);
                    //System.out.println("文件夹:" + f.getAbsolutePath());
                } else {
                    files.add(f.getAbsolutePath());
                    //System.out.println("文件:" + f.getAbsolutePath());
                }
            }
        }
        return files;
    }
}
