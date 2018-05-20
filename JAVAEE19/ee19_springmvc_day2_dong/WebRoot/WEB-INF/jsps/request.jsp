<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
<script type="text/javascript" src="${pageContext.request.contextPath }/js/jquery.js"></script>
<script type="text/javascript">
	function requestJson(){
		var jsonUser = JSON.stringify({"username":"帅东","address":"重庆"});
		$.ajax({
			type:'post',
			url:'${pageContext.request.contextPath }/user/requestJson.do',
			contentType:'application/json;charset=utf-8',
			data:jsonUser,
			success:function(data){
				alert(data.username);
			},
		});
	}
	function requestPojo(){
		$.ajax({
			type:'post',
			url:'${pageContext.request.contextPath }/user/requestPojo.do',
			data:'username=东东&address=America',
			success:function(data){
				alert(data.username);
			},
		});
	}
</script>
</head>
<body>
	<input type="button" value="请求json,返回json" onclick="requestJson()">
	<input type="button" value="请求pojo,返回json" onclick="requestPojo()">

</body>
</html>