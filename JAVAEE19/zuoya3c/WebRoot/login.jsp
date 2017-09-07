<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>陈明东</title>
<style type="text/css">
	#form{
		text-align: center;
		float: right;
		margin: 10px 16% 10px 0px;
	}
 	body{
		background-image: url("images/2.jpg");
		background-repeat: no-repeat;
 		background-color: #91DBFE;
	}
</style>

</head>
<body text="blue">
	<form action="${pageContext.request.contextPath }/servlet/LoginServlet" method="post" id="form">
		<br><br>
		<div>&nbsp;&nbsp;<font size="10" color="bule">账号登录</font></div><br>
		<div id="user"><font size="10" color="bule">姓名：</font><input type="text" name="username" id="username"></div><br>
		<div id="pwd"><font size="10" color="bule">密码：</font><input type="password" name="password"></div><br>
		&nbsp;&nbsp;<c:if test="${not empty u }"><font size="10" color="bule">账号密码不正确</font></c:if><br><br>
		&nbsp;&nbsp;<input type="submit" value="登录">
		<br>
	</form>
	
</body>
</html>