typedef struct NODE{
	int val;
	struct NODE *left;
	struct NODE *right;
	NODE(int val) :val(val), left(NULL), right(NULL){}
}Node, *Tree;

void create(Tree &p, int val);