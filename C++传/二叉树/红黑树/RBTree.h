
typedef key_t char;
typedef data_t char[10];

class RBTree
{
	struct RBNode
	{
		bool color;
		RBNode *parent;
		RBNode *left;
		RBNode *right;
	};
public:
	static RBNode* rb_rotate_left(RBNode* node, RBNode* root)
	{
		RBNode* right = node->right;
	}
	static RBNode* rb_rotate_right(RBNode* node, RBNode* root)
	{
		RBNode* right = node->right;
	}
	//三、红黑树查找结点 
	static RBNode* rb_search_auxiliary(key_t key, RBNode *root, RBNode **save)
	{

	}
	//返回上述rb_search_auxiliary查找结果  
	RBNode* rb_search(key_t key, RBNode* root)
	{
		return rb_search_auxiliary(key, root, nullptr);
	}
	//四、红黑树的插入  
	//---------------------------------------------------------  
	//红黑树的插入结点  
	RBNode* rb_insert(key_t key, data_t data, RBNode* root)
	{

	}
	//五、红黑树的3种插入情况
	//接下来，咱们重点分析针对红黑树插入的3种情况，而进行的修复工作。  
	//--------------------------------------------------------------  
	//红黑树修复插入的3种情况  
	//为了在下面的注释中表示方便，也为了让下述代码与我的倆篇文章相对应，  
	//用z表示当前结点，p[z]表示父母、p[p[z]]表示祖父、y表示叔叔。  
	//--------------------------------------------------------------  
	static RBNode* rb_insert_rebalance(RBNode *node, RBNode *root)
	{

	}
};