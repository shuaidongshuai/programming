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
		//pageContext.setAttribute("p", "pp");
		pageContext.setAttribute("p", "pp", PageContext.PAGE_SCOPE);
		
		//pageContext.setAttribute("p", "pp", PageContext.REQUEST_SCOPE);
		request.setAttribute("p", "request");
		
		//pageContext.setAttribute("p", "pp", PageContext.SESSION_SCOPE);
		session.setAttribute("p", "session");
		
		//pageContext.setAttribute("p", "pp", PageContext.APPLICATION_SCOPE);
		application.setAttribute("p", "application");
	 %>
	 
	 ${p }
	 
</body>
</html>