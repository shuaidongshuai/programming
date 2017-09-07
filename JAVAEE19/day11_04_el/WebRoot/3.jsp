<%@page import="java.util.HashMap"%>
<%@page import="java.util.Map"%>
<%@page import="java.util.ArrayList"%>
<%@page import="java.util.List"%>
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
		List list = new ArrayList();
		out.print(list.size());
		/* list.add("aaa");
		list.add("bbb");
		list.add("ccc"); */
		
		request.setAttribute("list", list);
		
		Map map = new HashMap();
		map.put("a", "aaaaa");
		map.put("b", "bbbbbb");
		map.put("c", "ccccc");
		
		request.setAttribute("m", map);
	 %>
	 
	 
	 ${list[1] }<br/>
	 
	 <%-- ${m["b"] } --%>
	 ${m.c }
</body>
</html>