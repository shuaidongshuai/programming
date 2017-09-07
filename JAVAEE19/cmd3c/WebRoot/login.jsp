<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>绿农优品</title>
<style type="text/css">
	.clear{
		clear:both;
	}
	body{
		background-image: url("images/login.jpg");
 		background-color: #F2F8BA;
 		background-repeat: no-repeat;
	}
	#form{
		background-color: #FAFBB7;
		float: right;
		margin: 5% 10% 0px;
		height: 50%;
		width: 30%;
		text-align: center;
	}
	#inside{
		margin: 6% 10%;
		background-color: #F9FCAF;
	}
	.logn{
		height: 50px;
		width: 300px;
		border: 1px solid #738282;
		margin: 5% 5%;
		font-family: "microsoft yahei";
	}
	#button{
		width: 300px;
		height: 40px;
		margin: -20px 10px 30px;
		background-color: #F6E138;
	}
	.logo{
		float: right;
		width: 30%;
		margin: -6% 0;
	}
	.input{
		vertical-align: 30%;	/*%	vertical-align 属性设置元素的垂直对齐方式。*/
		padding: 8px 10px;
		margin: 0px 0px 0px -9px;
	}
</style>

</head>
<body>
	<form action="${pageContext.request.contextPath }/servlet/LoginServlet" method="post" id="form">
		<div id="inside">
			<h1><font size="10" color="bule">账号登录</font></h1>
			<hr>
			<div class="logn">
				<font size="6" color="bule">姓名：</font>
				<input type="text" name="username" class="input">
			</div>
			<div class="logn">
				<font size="6" color="bule">密码：</font>
				<input type="password" name="password" class="input">
			</div>
			<div>
				<c:if test="${not empty u }"><font size="10" color="bule">账号密码不正确</font></c:if><br><br>
			</div>
			<input type="submit" value="登录" id="button"></input>
		</div>
		<span class="logo">东东独家赞助</span>
	</form>
</body>
</html>