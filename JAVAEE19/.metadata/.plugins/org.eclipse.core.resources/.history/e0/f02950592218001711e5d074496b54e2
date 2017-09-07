package com.dong.domain;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.HashMap;
import java.util.Map;

/**
 * 用于检查输入是否合法
 * 
 * @author ☆东★
 * 
 */
public class UserForm {
	private String username;
	private String password;
	private String repassword;
	private String email;
	private String birthday;

	public String getUsername() {
		return username;
	}

	public void setUsername(String username) {
		this.username = username;
	}

	public String getPassword() {
		return password;
	}

	public void setPassword(String password) {
		this.password = password;
	}

	public String getRepassword() {
		return repassword;
	}

	public void setRepassword(String repassword) {
		this.repassword = repassword;
	}

	public String getEmail() {
		return email;
	}

	public void setEmail(String email) {
		this.email = email;
	}

	public String getBirthday() {
		return birthday;
	}

	public void setBirthday(String birthday) {
		this.birthday = birthday;
	}

	public Map<String, String> getMsg() {
		return msg;
	}

	public void setMsg(Map<String, String> msg) {
		this.msg = msg;
	}

	// 用于回显数据
	Map<String, String> msg = new HashMap<String, String>();

	/*
	 * 用户名：必须输入，且3~8位的字母组成<br> 密码：必须输入，3~8位的数组组成<br> 确认密码：和密码保持一致<br>
	 * 邮箱：必须输入，且要符合邮箱的格式<br> 生日：必须输入，符合yyyy-MM-dd的格式<br>
	 */
	public boolean validate() {
		if (username==null || "".equals(username)) {
			msg.put("username", "密码不能为空！");
		} else if (username.length() < 3 || username.length() >= 20) {// 用户名：必须输入，且3~20位的字母组成<br>
			//msg.put("username", "用户名为3~8位的字母组成");
			msg.put("username", "用户名长度必须3~20");
		}

		if (password==null || "".equals(password)) {
			msg.put("password", "密码不能为空！");
		} //else if (!password.matches("\\d{3,8}")) {// 密码：必须输入，3~8位的数组组成<br>
		else if (password.length() < 6 || password.length() >= 20){
			msg.put("password", "密码为6~20位字母数字组成");
		} else if(!password.contains(".")){
			msg.put("password", "密码必须包含.");
		} else if(!password.matches(".*\\d+.*")){
			msg.put("password","密码必须包含数字");
		} else if(!password.matches(".*[a-zA-Z].*")){
			msg.put("password","密码必须包含字母");
		}

		// 确认密码：和密码保持一致<br>
		if (repassword==null || !repassword.equals(password)) {
			msg.put("repassword", "两次密码不一致！");
		}

		//邮箱：必须输入，且要符合邮箱的格式<br>
		if(email==null||"".equals(email)){
			msg.put("email", "邮箱不能为空！");
		}else if(!email.matches("\\b^['_a-z0-9-\\+]+(\\.['_a-z0-9-\\+]+)*@[a-z0-9-]+(\\.[a-z0-9-]+)*\\.([a-z]{2}|aero|arpa|asia|biz|com|coop|edu|gov|info|int|jobs|mil|mobi|museum|name|nato|net|org|pro|tel|travel|xxx)$\\b")){
			msg.put("email", "邮箱格式不正确！");
		}
		
		//生日：必须输入，符合yyyy-MM-dd的格式<br>
		if(birthday==null || "".equals(birthday)){
			msg.put("birthday", "生日不能为空！");
		}else {
			SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
			try {
				sdf.parse(birthday);
			} catch (ParseException e) {
				msg.put("birthday", "生日格式不正确！");
			}
		}
		return msg.isEmpty();//当map集合中没有数据时，返回true
	}

}
