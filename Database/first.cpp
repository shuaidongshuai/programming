/*练习mysql数据库的连接*/
#include <stdio.h>
#include <mysql.h>

int main()
{
	MYSQL mysql;
	int t, r;
	/*连接之前，先用mysql_init初始化MYSQL连接句柄*/
	mysql_init(&mysql);
	/*使用mysql_real_connect连接服务器,其参数依次为MYSQL句柄，服务器IP地址，
	登录mysql的用户名，密码，要连接的数据库等*/
	if(!mysql_real_connect(&mysql, "localhost", "root", "6748355", "spytest", 0, NULL, 0)) {
		printf("Error connecting to Mysql!\n");
	}else {
		printf("Connected Mysql successful!\n");
	}
	/*关闭连接*/
	mysql_close(&mysql);
	return 0;
}


/*练习mysql数据库的查询*/
#include <stdio.h>
#include <string.h>
#include "mysql.h"


int main()
{
	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *query;
	int flag, t;
	mysql_init(&mysql);
	if(!mysql_real_connect(&mysql, "localhost", "root", "dong", "plane", 0, NULL, 0)) {
		printf("Failed to connect to Mysql!\n");
		return 0;
	}else {
		printf("Connected to Mysql successfully!\n");
	}
	query = "select * from test2";
	/*查询，成功则返回0*/
	flag = mysql_real_query(&mysql, query, (unsigned int)strlen(query));
	if(flag) {
		printf("Query failed!\n");
		return 0;
	}else {
		printf("[%s] made...\n", query);
	}


	/*mysql_store_result讲全部的查询结果读取到客户端*/
	res = mysql_store_result(&mysql);
	/*mysql_fetch_row检索结果集的下一行*/
	while(row = mysql_fetch_row(res)) {
		/*mysql_num_fields返回结果集中的字段数目*/
		for(t=0; t<mysql_num_fields(res); t++)
		{
			printf("%s\t", row[t]);
		}
		printf("\n");
	}
	mysql_close(&mysql);
	return 0;
}


/*练习mysql数据库的数据添加*/
#include <stdio.h>
#include <string.h>
#include "mysql.h"


int main()
{
	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *query;
	int flag, t;
	mysql_init(&mysql);
	if(!mysql_real_connect(&mysql, "localhost", "root", "dong", "spytest", 0, NULL, 0)) {
		printf("Failed to connect to Mysql!\n");
		return 0;
	}else {
		printf("Connected to Mysql successfully!\n");
	}
	query = "insert into log(title, keyword, content) values('sleep', 'rest', 'I have a dream')";
	/*插入，成功则返回0*/
	flag = mysql_real_query(&mysql, query, (unsigned int)strlen(query));
	if(flag) {
		printf("Insert data failure!\n");
		return 0;
	}else {
		printf("Insert data success!\n");
	}


	mysql_close(&mysql);
	return 0;
}


/*练习mysql数据库的删除*/
#include <stdio.h>
#include <string.h>
#include "mysql.h"

int main()
{
	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *query;
	int flag, t;
	mysql_init(&mysql);
	if(!mysql_real_connect(&mysql, "localhost", "root", "6748355", "spytest", 0, NULL, 0)) {
		printf("Failed to connect to Mysql!\n");
		return 0;
	}else {
		printf("Connected to Mysql successfully!\n");
	}
	query = "delete from log where log_id=3";
	/*删除，成功则返回0*/
	flag = mysql_real_query(&mysql, query, (unsigned int)strlen(query));
	if(flag) {
		printf("Delete data failure!\n");
		return 0;
	}else {
		printf("Delete data success!\n");
	}

	mysql_close(&mysql);
	return 0;
}