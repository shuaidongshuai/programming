<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<%@taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <title>My JSP 'index.jsp' starting page</title>
  </head>
  
  <body>
   		<!-- 声明一个变量 num -->
   		<c:set var="num" value="10" scope="session"></c:set>
   		
   		输出变量：<%-- <c:out value="${num }"></c:out> --%>${num }
   		
   		<c:remove var="num" scope="session"/>
   		
   		输出变量：<c:out value="${num }" default="aaa"></c:out>
  </body>
</html>
