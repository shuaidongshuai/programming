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
	span{
		font-size: 30px;
	}
	.two{
		padding: 0px 59px 0px 0px;
	}
	.three{
		padding: 0px 24px 0px 0px;
	}
	body{
		background-color: gray;
		background-image: url("images/2.jpg");
		/* background-repeat: repeat-y; */
	}
	#reg{
		margin: 0px 0px 0px 10px;
		width: 300px;
		height: 30px;
		color: #B79184;
		background-color: green;
		border-color: black;
	}
</style>
<body text = "red" background="images/2.jpg">
	<form action="${pageContext.request.contextPath }/servlet/RegServlet"
		method="post" id="form">
		<br>
		<div id="page">
			<span class="three">用户名：</span>
			<input type="text" name="username" value="${uf.username }">${uf.msg.username }${error }<br><br>
			<span class="two">密码：</span><input type="password" name="password" value="${uf.password }">${uf.msg.password }<br> <br>
			<span >确认密码：</span><input type="password" name="repassword" value="${uf.repassword }">${uf.msg.repassword }<br> <br>
			<span class="two">邮箱：</span><input type="text" name="email" value="${uf.email }">${uf.msg.email }<br> <br>
			<span class="two">生日：</span><input	type="text" name="birthday" value="${uf.birthday }">
			<c:if test="${empty uf.msg.birthday }">
			例：1996-2-22
			</c:if>
			${uf.msg.birthday }<br><br>
			<input	type="submit" value="注册" id="reg"><br>
		</div>
	</form>

</body>
</html>