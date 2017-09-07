/*练习mysql数据库的数据添加*/
#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>


int main()
{
	printf("Content-type:text/html\n\n");
	
	char* arg = getenv("QUERY_STRING");
    // arg = id=1000&name=user_1122
	strtok(arg, "=&");
	char* name = strtok(NULL, "=&");
        strtok(NULL, "=&");
        char* id = strtok(NULL, "=&");	

	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int flag;
	mysql_init(&mysql);
	if(!mysql_real_connect(&mysql, "localhost", "root", "dong", "plane", 0, NULL, 0)) {
		printf("Failed to connect to Mysql!\n");
		return 0;
	}else {
		printf("Connected to Mysql successfully!\n");
	}
	char cmd[1024];
	sprintf(cmd,"insert into score values('%s',%s)",name,id);
	/*插入，成功则返回0*/
	flag = mysql_query(&mysql, cmd);
	if(flag) {
		printf("Insert data failure!\n");
		return 0;
	}else {
		printf("Insert data success!\n");
	}

	mysql_close(&mysql);
	return 0;
}
