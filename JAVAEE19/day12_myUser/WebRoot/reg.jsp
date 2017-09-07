<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>陈明东</title>
</head>
<style type="text/css">
	#form{
		text-align: left ;
	}
	body{
		background-color: gray;
		background-image: url("images/2.jpg");
		background-repeat: repeat-y;
	}
</style>
<body text = "red" background="images/2.jpg">
	<form action="${pageContext.request.contextPath }/servlet/RegServlet"
		method="post" id="form">
		<br><br><br><br>
		&nbsp;用户名：<input type="text" name="username" value="${uf.username }">${uf.msg.username }${error }<br><br>
		 &nbsp;&nbsp;密码：<input type="password" name="password" value="${uf.password }">${uf.msg.password }<br> <br>
		确认密码：<input type="password" name="repassword" value="${uf.repassword }">${uf.msg.repassword }<br> <br>
		&nbsp;&nbsp;邮箱：<input type="text" name="email" value="${uf.email }">${uf.msg.email }<br> <br>
		&nbsp;&nbsp;生日：<input	type="text" name="birthday" value="${uf.birthday }">
		<c:if test="${empty uf.msg.birthday }">
		例：1996-2-22
		</c:if>
		${uf.msg.birthday }<br><br>
		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input	type="submit" value="注册"><br>
	</form>

</body>
</html>