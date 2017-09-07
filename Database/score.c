#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>

int main()
{
    printf("Content-type:text/html\n\n");

    char* arg = getenv("QUERY_STRING");

    strtok(arg, "=&");
    char* name = strtok(NULL, "=&");
    strtok(NULL, "=&");
    char* score = strtok(NULL, "=&");

	MYSQL conn;
	MYSQL_RES* res;
	MYSQL_ROW row;
	char query[1024];
	
	mysql_init(&conn);
	if(!mysql_real_connect(&conn,"localhost","root","dong","plane",0,NULL,0))
	{
		printf("Failed to &connect to Mysql! <br>\n");
		return 0;
	}else {
		printf("&connected to Mysql successfully! <br>\n");
	}
	
	//插入
	sprintf(query,"insert into score values('%s',%s)",name,score);
	//成功则返回0*
	if(mysql_query(&conn,query))
	{
		printf("Insert data failure! <br>\n");
                return 0;
     }

	 //查询
	 sprintf(query,"select * from score order by score desc limit 15");
	if(mysql_query(&conn,query))
	{
		printf("%s\n", mysql_error(&conn));
        exit(1);
	}
	
	res = mysql_use_result(&conn);
	
	while((row = mysql_fetch_row(res))!=NULL)
	{
		// for(int i = 0;i<mysql_num_fields(res);i++)
		// {
			// printf("|%s",row[i]);
		// }
		printf("|%s|%s",row[0],row[1]);
	}
	//mysql_free_result(res);
	mysql_close(&conn);
	return 0;
}
