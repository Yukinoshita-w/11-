#include<iostream>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
//���������ṹ�����ۣ�
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
	// ʹ��һ�������������ڵ�
	int index = 0;
	// �������ڵ�
	if (nodes[index] != 0) {
		root = new TreeNode(nodes[index]);
		que.push(root);
	}
	index++;
	while (!que.empty() && index < nodes.size()) {
		cur = que.front();
		que.pop();

		// ���ӽڵ�
		if (index < nodes.size() && nodes[index] != 0) {
			cur->left = new TreeNode(nodes[index]);
			que.push(cur->left);
		}
		index++;
		// ���ӽڵ�
		if (index < nodes.size() && nodes[index] != 0) {
			cur->right = new TreeNode(nodes[index]);
			que.push(cur->right);
		}
		index++;
	}
	return root;
}

//�������򡢺�������ĵݹ��㷨
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
//�������򡢺�������ķǵݹ��㷨
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
//����������ǵݹ飩//��
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
	vector<int> v = { 1, 5, 2, 3, 4, 8, 9, 1, 7 }; // ʹ�ô����ų�ʼ��
	TreeNode* T = createTree(v);

	vector<int> ans;

	// ������������������ݹ飩
	Preorder(T, ans);
	cout << "����������ݹ飩:";
	print(ans);
	// ��� ans ����
	ans.clear();
	// ���������������
	Inorder(T, ans);
	cout << "����������ݹ飩:";
	print(ans);
	// ��� ans ����
	ans.clear();
	// ���ú�������������ݹ飩
	Postorder(T, ans);
	cout << "����������ݹ飩:";
	print(ans);
	// ��� ans ����
	ans.clear();
	// ������������������ǵݹ飩
	ans = PreorderTraversal(T);
	cout << "����������ǵݹ飩:";
	print(ans);
	// ��� ans ����
	ans.clear();
	// ������������������ǵݹ飩
	ans = InorderTraversal(T);
	cout << "����������ǵݹ飩:";
	print(ans);
	// ��� ans ����
	ans.clear();
	// ���ú�������������ǵݹ飩
	ans = PostorderTraversal(T);
	cout << "����������ǵݹ飩:";
	print(ans);
	ans.clear();
	// ���ú�������������ǵݹ飩��
	ans = PostorderTraversal_1(T);
	cout << "����������ǵݹ飩��:";
	print(ans);
	return 0;
}