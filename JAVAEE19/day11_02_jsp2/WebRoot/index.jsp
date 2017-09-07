<%@ page language="java" import="java.util.*" pageEncoding="UTF-8" contentType="text/html; charset=UTF-8"%>


<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <title>My JSP 'index.jsp' starting page</title>
  </head>
  
  <body>
  
  <!-- 这是HTML注释 -->
  <%-- 这是JSP注释 --%>
    	<%!
    		int num1=10;
    		public void show(){
    		}
    	 %>
    	<%
    		int num2 = 10;
    		num1++;
    		num2++;
    		//out.print(num1+3);
    		session.setAttribute("aa", "asfd");
    	 %>
    	 
    	 <%=num1 %>
    	 <%=num2 %>
  </body>
</html>
