<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>


<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
	<head>
		
		<title>Insert title here</title>
	</head>
	<body>
		<!-- el表达式用没有request的对象，想要获取request对象。只能通过pageContext来获取 -->
		<form action="${pageContext.request.contextPath }/success.jsp" method="post">
			用户名：<input type="text" name="userName" /><br /> 密码：<input
				type="password" name="pwd" /><br /> <input type="submit" value="登录" /><br />
		</form>
	</body>
</html>