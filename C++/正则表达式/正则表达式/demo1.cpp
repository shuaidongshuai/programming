#include <iostream>
#include <regex>
#include <string>
using namespace std;

/*
验证网址
*/
int test()
{
	string html;
	getline(cin, html);

	string pattern("http(s)?://([\\w-]+\\.)+[\\w-]+(/[\\w- ./?%&=]*)?");
	pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
	regex r(pattern);
	for (sregex_iterator it(html.begin(), html.end(), r), end;     //end是尾后迭代器，regex_iterator是regex_iterator的string类型的版本
		it != end;
		++it)
	{
		cout << it->str() << endl;
	}
	getchar();
	return 0;
}