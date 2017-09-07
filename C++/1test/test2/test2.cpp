#include <iostream>
#include <string>
using namespace std;

class Link
{
public:
	char data;
	Link *next;
};
///////////////////////////////////////////////////////////////////////////
int get_list_len(Link *link)
{
	int count = 0;
	while (link)
	{
		++count;
		link = link->next;
	}
	return count;
}
Link *find_first_public(Link *link1, Link *link2)
{
	/* 先把两个链表弄成一样长 */
	Link *long_link;
	Link *short_link;
	int len1 = get_list_len(link1);
	int len2 = get_list_len(link2);
	int count;
	if (len1 > len2)
	{
		long_link = link1;
		short_link = link2;
		count = len1 - len2;
	}
	else
	{
		long_link = link2;
		short_link = link1;
		count = len2 - len1;
	}
	while (count)
	{
		--count;
		long_link = long_link->next;
	}
	/* 第一个相同的节点即为公共节点 */
	while (long_link)
	{
		if (long_link->data == short_link->data)
			return long_link;
	}
	return NULL;
}
///////////////////////////////////////////////////////////////////////////
Link* create_link(string s)
{
	int len = s.size();
	Link *head = new Link();
	Link *link = head;
	string::iterator it = s.begin();
	while (it != s.end())
	{
		--len;
		link->data = *it;
		++it;
		link = link->next;
	}
	link->next = NULL;
	link = head;
	while (link)
	{
		cout << link->data << " ";
		link = link->next;
	}
	cout << endl;
	return head;
}

int test2()
{
	Link *link1 = create_link("dong");
	Link *link2 = create_link("shuai dong");
	Link *link3 = create_link("usin");
	return 0;
}