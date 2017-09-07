<%@page import="com.itheima.entity.Student"%>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>
	<%
		Student stu = new Student();
		stu.setName("tom");
		
		out.print(stu.getName());
		
		//request.getRequestDispatcher("/7.jsp").forward(request, response);
		
		
	 %>
	 
	 <jsp:useBean id="stu1" class="com.itheima.entity.Student"></jsp:useBean>
	 <jsp:setProperty property="name" name="stu1" value="jerry"/>
	 <jsp:getProperty property="name" name="stu1"/>
	 
	 <!-- http://localhost:8080/day11_02_jsp2/6.jsp?name=123 -->
	 <jsp:forward page="/7.jsp">
	 	<jsp:param value="123" name="name"/>
	 	<jsp:param value="333" name="pwd"/>
	 </jsp:forward>
</body>
</html>