<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>My JSP 'index.jsp' starting page</title>
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->
  </head>
  
  <body>
  	<h1>Hello Dong</h1>
  	
  	<h1>receiveInt</h1>
  	<!-- 这里的name要和UserController中的参数一致 -->
  	<form action="${pageContext.request.contextPath }/user/receiveInt.do">
		ID：<input type="text" name="id">
		<input type="submit" value="提交">
	</form>
	
	<h1>receiveInts</h1>
	<form action="${pageContext.request.contextPath }/user/receiveInts.do" method="post">
		ID：<input type="checkbox" name="ids" value="1">
		ID：<input type="checkbox" name="ids" value="2">
		ID：<input type="checkbox" name="ids" value="3">
		<input type="submit" value="提交">
	</form>
	
	<h1>receiveStr</h1>
  	<form action="${pageContext.request.contextPath }/user/receiveStr.do">
		Name：<input type="text" name="name">
		<input type="submit" value="提交">
	</form>
	
	<h1>receiveUser</h1>
  	<form action="${pageContext.request.contextPath }/user/receiveUser.do">
		姓名：<input type="text" name="username">
		生日：<input type="text" name="birthday">
		性别：<input type="text" name="sex">
		地址：<input type="text" name="address">
		<input type="submit" value="提交">
	</form>
	
	<h1>receiveUserCustom</h1>
	<form action="${pageContext.request.contextPath }/user/receiveUserCustom.do">
		姓名：<input type="text" name="user.username">
		生日：<input type="text" name="user.birthday">
		性别：<input type="text" name="user.sex">
		地址：<input type="text" name="user.address">
		<input type="submit" value="提交">
	</form>
	
	<h1>receiveList</h1>
	<form action="${pageContext.request.contextPath }/user/receiveList.do">
		姓名1：<input type="text" name="userList[0].username">
		姓名2：<input type="text" name="userList[1].username">
		<input type="submit" value="提交">
	</form>
	
	<h1>receiveMap</h1>
	<form action="${pageContext.request.contextPath }/user/receiveMap.do">
		姓名：<input type="text" name="maps['username']">
		地址：<input type="text" name="maps['address']">
		<input type="submit" value="提交">
	</form>
	
  </body>
</html>
