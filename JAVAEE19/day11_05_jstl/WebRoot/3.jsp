<%@page import="java.util.ArrayList"%>
<%@page import="java.util.List"%>
<%@ page    pageEncoding="UTF-8"%>
 <%@taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>
<%-- 	<c:forEach var="i" begin="1" end="10" step="2"> 
		${i }<br/>
	</c:forEach> --%>
	
	
	<%
		List list = new ArrayList();
		list.add("aaa");
		list.add("bbb");
		list.add("ccc");
		
		request.setAttribute("list", list);
	 %>
	<c:forEach items="${list }" var="l">
		${l }
	</c:forEach>
</body>
</html>