#include<iostream>
#include <vld.h>

#define LINKSIZE 27
#define KEYSIZE 26

typedef enum {ELEM = 0,BRCH}NodeType;
typedef struct{} Record;
typedef struct
{

};

class BNode;

typedef struct
{
	BNode *pnode;
	int index;
	bool tag;
}Result;

class BNode
{
public:
	BNode *next[LINKSIZE];
	
};


int main()
{

}