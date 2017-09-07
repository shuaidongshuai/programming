<%@page import="java.util.List"%>
<%@page import="java.util.ArrayList"%>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Insert title here</title>

<style type="text/css">
	.blue{
		background-color: blue;
	}
	.green{
		background-color: green;
	}
</style>

</head>
<body>
	<%
		List list = new ArrayList();
		list.add("aa");
		list.add("bb");
		list.add("cc");
		list.add("dd");
		request.setAttribute("list", list);
	 %>
	 
	 <table border="1">
	 	<tr>
	 		<th>数据
	 		<th>索引
	 		<th>计数
	 		<th>是否是第一个
	 		<th>是否是最后一个
	 
	 <!-- 循环这个list 并且每循环一次，都输出一行 -->
	  <c:forEach items="${list }" var="l" varStatus="vs">
	 	<tr class="${vs.index%2==0?'blue':'green' }">
	 		<td>${l }
			<td>${vs.index }
			<td>${vs.count }
			<td>${vs.first }
			<td>${vs.last }
	 </c:forEach>
	 
	 </table>
	
</body>
</html>