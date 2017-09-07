#include <iostream>
#include <regex>
#include <string>
using namespace std;

void test2()
{
	string html;
	while (1)
	{
		getline(cin, html);

		string pattern("([0-9a-eA-E])");

		regex r(pattern);
		for (sregex_iterator it(html.begin(), html.end(), r), end; it != end; ++it)
		{
			cout << it->str();
		}
		cout << endl;
	}
}