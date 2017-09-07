<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
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
	
	<style type="text/css">
		#d{
			text-align: center;
		}
	</style>
	
  </head>
  
  <body background="images/1.jpg">
  	<p align="center" >
  		<font size="50" color="red">欢迎来到东东招聘网站</font>
  	</p>
  	<div id="d">
  		<br><br><br><br><br><br><br><br><br>
  	 	<c:if test="${empty u }">
	    <a href="login.jsp" id="login"><font size="20" color="green">登录</font></a>
	    &nbsp;&nbsp;&nbsp;&nbsp;
	    <a href="reg.jsp" id="reg"><font size="20" color="blue">注册</font></a>
	  	</c:if>
	  	<c:if test="${not empty u }">
	  		<font size="20" color="yellow">O(∩_∩)O~<br>欢迎你：${u.username }</font><br><br>
	  		<a href="${pageContext.request.contextPath }/Frameset.html"><font size="20" color="red">进入招聘网</font></a>
	  		<a href="${pageContext.request.contextPath }/servlet/OutServlet"><font size="20" color="black">注销</font></a>
	  	</c:if>
  	</div>
 
  	
  </body>
</html>
