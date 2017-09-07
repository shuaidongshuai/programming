<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <title>My JSP 'index.jsp' starting page</title>
  </head>
  <body>
  <!-- html注释 		特点：不安全，费流量    -->
    <%--	jsp注释 		特点：安全，省流量
    	Date d = new Date();
    	out.write(d.toLocaleString());
     --%>
     <%!
     	int num2 = 10;/* 全局变量 */
      %>
     <%
     	int num1 = 10;/* 局部变量 */
     	num1++;
     	num2++;
     	out.print(num1+"&nbsp;");
     	out.print(num2);
     	out.print("<br>-------------------<br>");
      %>
      <%=num1%>
      <%=num2 %> 
  </body>
</html>
