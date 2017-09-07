#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
int main() 
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char server[] = "localhost";
    char user[] = "root";
    char password[] = "dong";
    char database[] = "plane";
    
    conn = mysql_init(NULL);
    
    if (!mysql_real_connect(conn, server,user, password, database, 0, NULL, 0)) 
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    
    if (mysql_query(conn, "select * from test2 order by id desc limit 3;"))//mysql_query -- 发送一条 MySQL 查询。
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    
    res = mysql_use_result(conn);
    
    
    while ((row = mysql_fetch_row(res)) != NULL)
    {
		/*mysql_num_fields返回结果集中的字段数目*/
		for(int t=0; t<mysql_num_fields(res); t++)
		{
			printf("%s\t", row[t]);
		}
		printf("\n");
//        printf("%s %s\n", row[0],row[1]);
    }
    
    mysql_free_result(res);
    mysql_close(conn);
    return 0;
}
