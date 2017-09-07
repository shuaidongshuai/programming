<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>
	<!-- param  用于取表单参数  -->
	<hr>欢迎你：${param.userName } <!-- ${param.userName }==request.getParamemter("userName"); -->

	<hr>${paramValues.hobby[0] }
	
	<%-- ${header["User-agent"] } --%>
	
	<hr>${cookie.JSESSIONID.value }<!-- 获取cookie值 -->
</body>
</html>