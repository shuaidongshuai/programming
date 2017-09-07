#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>


int main()
{
	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int flag;
	mysql_init(&mysql);
	if(!mysql_real_connect(&mysql, "localhost", "root", "dong", "dong", 0, NULL, 0)) {
		printf("Failed to connect to Mysql!\n");
		return 0;
	}else {
		printf("Connected to Mysql successfully!\n");
	}
	char query[50] = "select id from info";
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
	while(row = mysql_fetch_row(res)) 
	{
		
		/*mysql_num_fields返回结果集中的字段数目*/
		for(int t=0; t<mysql_num_fields(res); t++)
		{
			//printf("%s\n",row[t]);
			sprintf(query,"insert into score values('%s',%d);",row[t],rand()%50 + 50);
			/*插入，成功则返回0*/
			flag = mysql_real_query(&mysql, query, (unsigned int)strlen(query));
			if(flag) {
				printf("Insert data failure!\n");
				return 0;
			}else {
				printf("Insert data success!\n");
			}
		}
	}
	
	mysql_close(&mysql);
	return 0;
}
