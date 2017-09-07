<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %><!-- prefix  前缀 -->
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Insert title here</title>
</head>
<body>

	<!-- 相当于if -->
	<c:if test="${5>3 }">
	5>3
	</c:if>
	
	<c:set var="num" value="5"></c:set>
	
	<!-- 相当于 catch -->
	<c:choose>
		<c:when test="${num == 1 }">111111111111111</c:when>
		<c:when test="${num == 2 }">2222222222222</c:when>
		<c:when test="${num == 3 }">33333333333</c:when>
		<c:otherwise>
		otherwise
		</c:otherwise>
	</c:choose>
	
	
	
</body>
</html>