#include<iostream>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
//二叉树结点结构（力扣）
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
TreeNode* createTree(vector<int> nodes) {
	if (nodes.empty()) {
		return nullptr;
	}
	queue<TreeNode*> que;
	TreeNode* root = nullptr;
	TreeNode* cur = nullptr;
	// 使用一个索引来遍历节点
	int index = 0;
	// 创建根节点
	if (nodes[index] != 0) {
		root = new TreeNode(nodes[index]);
		que.push(root);
	}
	index++;
	while (!que.empty() && index < nodes.size()) {
		cur = que.front();
		que.pop();

		// 左子节点
		if (index < nodes.size() && nodes[index] != 0) {
			cur->left = new TreeNode(nodes[index]);
			que.push(cur->left);
		}
		index++;
		// 右子节点
		if (index < nodes.size() && nodes[index] != 0) {
			cur->right = new TreeNode(nodes[index]);
			que.push(cur->right);
		}
		index++;
	}
	return root;
}

//先序、中序、后序遍历的递归算法
void Preorder(TreeNode* root, vector<int>&v) {
	if (root == NULL)return;
	else {
		v.push_back(root->val);
		Preorder(root->left, v);
		Preorder(root->right, v);
	}
}
void Inorder(TreeNode* root, vector<int>&v) {
	if (root == NULL)return;
	else {
		Inorder(root->left, v);
		v.push_back(root->val);
		Inorder(root->right, v);
	}
}
void Postorder(TreeNode* root, vector<int>&v) {
	if (root == NULL)return;
	else {
		Postorder(root->left, v);
		Postorder(root->right, v);
		v.push_back(root->val);
	}
}
//先序、中序、后序遍历的非递归算法
vector<int> PreorderTraversal(TreeNode* root) {
	vector<int>v;
	stack<TreeNode*>s;
	TreeNode* p;
	p = root;
	while (p || !s.empty()) {
		if (p) {
			v.push_back(p->val);
			s.push(p);
			p = p->left;
		}
		else {
			p = s.top();
			s.pop();
			p = p->right;
		}
	}
	return v;
}

vector<int> InorderTraversal(TreeNode* root) {
	vector<int>v;
	stack<TreeNode*>s;
	TreeNode* p = root;
	while (p || !s.empty()) {
		if (p) {
			s.push(p);
			p = p->left;
		}
		else {
			TreeNode* q = s.top();
			s.pop();
			v.push_back(q->val);
			p = q->right;
		}
	}
	return v;
}
vector<int> PostorderTraversal(TreeNode* root) {
	vector<int>v;
	stack<TreeNode*>s;
	TreeNode* p;
	TreeNode* visit = NULL;
	p = root;
	while (p || !s.empty()) {
		if (p) {
			s.push(p);
			p = p->left;
		}
		else {
			TreeNode* top = s.top();
			if (top->right && top->right != visit) {
				p = top->right;
			}
			else {
				v.push_back(top->val);
				visit = top;
				s.pop();
			}
		}
	}
	return v;
}
//后序遍历（非递归）//简化
vector<int> PostorderTraversal_1(TreeNode* root) {
	stack<TreeNode*> st;
	vector<int> result;
	if (root == NULL) return result;
	st.push(root);
	while (!st.empty()) {
		TreeNode* node = st.top();
		st.pop();
		result.push_back(node->val);
		if (node->left) st.push(node->left);
		if (node->right) st.push(node->right);
	}
	reverse(result.begin(), result.end());
	return result;
}
void print(vector<int>v) {
	for (int i : v) {
		cout << i << " ";
	}
	cout << endl;
}
int main() {
	vector<int> v = { 1, 5, 2, 3, 4, 8, 9, 1, 7 }; // 使用大括号初始化
	TreeNode* T = createTree(v);

	vector<int> ans;

	// 调用先序遍历函数（递归）
	Preorder(T, ans);
	cout << "先序遍历（递归）:";
	print(ans);
	// 清空 ans 向量
	ans.clear();
	// 调用中序遍历函数
	Inorder(T, ans);
	cout << "中序遍历（递归）:";
	print(ans);
	// 清空 ans 向量
	ans.clear();
	// 调用后序遍历函数（递归）
	Postorder(T, ans);
	cout << "后序遍历（递归）:";
	print(ans);
	// 清空 ans 向量
	ans.clear();
	// 调用先序遍历函数（非递归）
	ans = PreorderTraversal(T);
	cout << "先序遍历（非递归）:";
	print(ans);
	// 清空 ans 向量
	ans.clear();
	// 调用中序遍历函数（非递归）
	ans = InorderTraversal(T);
	cout << "中序遍历（非递归）:";
	print(ans);
	// 清空 ans 向量
	ans.clear();
	// 调用后序遍历函数（非递归）
	ans = PostorderTraversal(T);
	cout << "后序遍历（非递归）:";
	print(ans);
	ans.clear();
	// 调用后序遍历函数（非递归）简化
	ans = PostorderTraversal_1(T);
	cout << "后序遍历（非递归）简化:";
	print(ans);
	return 0;
}