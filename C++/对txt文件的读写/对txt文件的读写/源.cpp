#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
using namespace std;

int main()
{
	FILE* fp = NULL;
	fp = fopen("dong.txt", "w+");

	char buf = 1;
	char buff[10];
	fwrite(&buf, 1, 1, fp);

	fseek(fp, 0, SEEK_SET);

	fread(buff, 1, 1, fp);

	int i = buff[0];
	cout << i << endl;
	fclose(fp);

	cin.get();
	return 0;
}

int main1()
{
	FILE*stream;
	char msg[] = "1";
	char buf[20];
	if ((stream = fopen("DUMMY.FIL", "w+")) == NULL)
	{
		fprintf(stderr, "Can not open output file.\n");
		return 0;
	}
	/*write some data to the file*/
	fwrite(msg, 1, strlen(msg) + 1, stream);
	/*sizeof£¨char£©=1 seek to the beginning of the file*/
	fseek(stream, 0, SEEK_SET);
	/*read the data and display it*/
	fread(buf, 1, strlen(msg) + 1, stream);
	printf("%s\n", buf);
	fclose(stream);

	cin.get();
	return 0;
}