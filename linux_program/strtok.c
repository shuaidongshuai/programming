#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
	//char* arg = getenv("QUERY_STRING");
	// arg = score=1000&username=user_1122
	char str[] = "username=dong&score=100";
	char *delim = "=&";
	
	char *temp = strtok(str, delim);
	printf("第一次截断：%s\n",temp);
	
	char* username = strtok(NULL, delim);
	printf("第二次截断：%s\n",username);
	
	temp = strtok(NULL, delim);
	printf("第三次截断：%s\n",temp);
	
	char* score = strtok(NULL, delim);
	printf("第四次截断：%s\n", score);

}
