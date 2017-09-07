class Solution {
public:
	int min(int a, int b)
	{
		return a<b ? a : b;
	}
	int run(TreeNode *root) {
		if (root == NULL)
			return 0;
		int left = run(root->left);
		int right = run(root->right);

		/*这里就是和求高度的区别了，当左边或者右边为空的时候，就不能取为空的那一边了*/
		if (left == 0 || right == 0)
			return left + right + 1;

		return min(left, right) + 1;
	}
};