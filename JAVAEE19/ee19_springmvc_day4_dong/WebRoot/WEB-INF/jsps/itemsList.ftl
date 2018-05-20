<#assign picPath="http://127.0.0.1:8081/picService" />
<#assign projectName="ee19_springmvc_day4_dong" />
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>查询商品列表</title>
</head>
<body>
	<form action="${projectName}/items/deleteByIds.do"
		method="post">
		查询条件：
		<table width="100%" border=1>
			<tr>
				<td><input type="submit" value="批量删除" /></td>
			</tr>
		</table>
		商品列表：
		<table width="100%" border=1>
			<tr>
				<td>ID</td>
				<td>商品名称</td>
				<td>商品图片</td>
				<td>商品价格</td>
				<td>商品描述</td>
				<td>操作</td>
			</tr>
			<#list itemsList as item>
				<tr>
					<td><input type="checkbox" name="ids" value="${item.id }"></td>
					<td>${item.name }</td>
					<td><img id='imgSize1ImgSrc' src='${picPath }${item.pic }'
						height="100" width="100" /></td>
					<td>${item.price }</td>
					<td>${item.detail }</td>
					<td><a
						href="${projectName}/items/edit.do?id=${item.id}">修改</a>
						<a
						href="${projectName}/items/deleteById.do?id=${item.id}">删除</a>
					</td>
				</tr>
			</#list>
		</table>
	</form>
</body>

</html>