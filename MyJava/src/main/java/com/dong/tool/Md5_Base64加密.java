package com.dong.tool;

import org.apache.commons.codec.binary.Base64;

import java.security.MessageDigest;

/**
 * @author dong
 */
public class Md5_Base64加密 {
    public static String doSign(String content, String charset, String keys) {
        String sign = "";
        content = content + keys;
        try {
            MessageDigest md = MessageDigest.getInstance("MD5");
            md.update(content.getBytes(charset));
            sign = new String(Base64.encodeBase64(md.digest()), charset);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
        return sign;
    }

    public static void main(String[] args) {
        System.out.println(doSign("{\"arg0\":{\"logs\":[\"2018-11-19 10:10:25,176 INFO - connect_success\"]}}", "utf-8", "cniotp"));
        System.out.println(doSign("{\"arg0\":{\"logs\":[\"2018-11-19 10:10:25,176 INFO - connect_success\"]}}", "gbk", "cniotp"));
    }
}
