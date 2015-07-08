#include "tree_traversal.h"

#include <stdio.h>

#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

#include "test.h"
#include "time_util.h"
#include "tree.h"

using std::cout;
using std::endl;
using std::fstream;
using std::queue;
using std::string;
using std::stringstream;

extern fstream ofs;

static vector<string> in_files, out_files;

int create_tree(const string &_file_name, TreeNode **_root)
{
	TreeNode *root = NULL;

	fstream infs(_file_name.c_str(), fstream::in);
	if (!infs) {
		fprintf(stderr, "failed to open(%s)\n", _file_name.c_str());
		return -1;
	}

	string line;
	queue<TreeNode*> node_q;

	if (std::getline(infs, line)) {
		stringstream ss(line);
		int val;
		ss >> val;
		// cout << "height is : " << val << endl;
	}

	if (std::getline(infs, line)) {
		stringstream ss(line);
		int val;
		ss >> val;
		root = new TreeNode(val);
		node_q.push(root);
	}

	string word;

	while (std::getline(infs, line)) {
		int iii = 0;
		TreeNode *parent_node;
		stringstream ss(line);
		while (ss >> word) {
			if (0 == iii % 2) {
				parent_node = node_q.front();
				node_q.pop();
			}
			if (NULL == parent_node)
				node_q.push(NULL);
			else {
				if ("#" == word)
					node_q.push(NULL);
				else {
					TreeNode *node = new TreeNode(str_to_int(word));
					if (0 == iii % 2)
						parent_node->left = node;
					else
						parent_node->right = node;
					node_q.push(node);
				}
			}
			iii++;
		}
	}

	*_root = root;
	infs.close();
	return 0;
}

void free_tree(TreeNode *root)
{
	while (root) {
		free_tree(root->left);
		free_tree(root->right);
		delete root;
		root = NULL;
	}
}

int TEST_preorderTraversal_recursively()
{
	TimeUtil tu;

	if (0 != get_files("tree_traversal_test_data/preorder", &in_files, &out_files))
		return -1;
	for (int iii = 0; iii < in_files.size(); iii++) {
		const string in_file_name = in_files[iii];

		TreeNode *root;
		if (0 != create_tree(in_file_name, &root))
			return -1;

		// Run
		ofs.open(OUTPUT_FILE, fstream::out);
		tu.restart();

		preorderTraversal_recursively(root);

		tu.stop();
		ofs.close();

		if (0 != compare_file(out_files[iii], OUTPUT_FILE)) {
			cout << __FUNCTION__ << " failed  :" << endl;
			return -1;
		}

		free_tree(root);
	}
	cout << __FUNCTION__ << "  total run time=" << tu.get_total_run_time() << "ms" << endl;

	return 0;
}

int TEST_preorderTraversal_iteratively()
{
	TimeUtil tu;

	if (0 != get_files("tree_traversal_test_data/preorder", &in_files, &out_files))
		return -1;
	for (int iii = 0; iii < in_files.size(); iii++) {
		const string in_file_name = in_files[iii];

		TreeNode *root;
		if (0 != create_tree(in_file_name, &root))
			return -1;

		// Run
		ofs.open(OUTPUT_FILE, fstream::out);
		tu.restart();

		preorderTraversal_iteratively(root);

		tu.stop();
		ofs.close();

		if (0 != compare_file(out_files[iii], OUTPUT_FILE)) {
			cout << __FUNCTION__ << " failed  :" << endl;
			return -1;
		}

		free_tree(root);
	}
	cout << __FUNCTION__ << "  total run time=" << tu.get_total_run_time() << "ms" << endl;

	return 0;
}

int TEST_inorderTraversal_recursively()
{
	TimeUtil tu;

	if (0 != get_files("tree_traversal_test_data/inorder", &in_files, &out_files))
		return -1;
	for (int iii = 0; iii < in_files.size(); iii++) {
		const string in_file_name = in_files[iii];

		TreeNode *root;
		if (0 != create_tree(in_file_name, &root))
			return -1;

		// Run
		ofs.open(OUTPUT_FILE, fstream::out);
		tu.restart();

		inorderTraversal_recursively(root);

		tu.stop();
		ofs.close();

		if (0 != compare_file(out_files[iii], OUTPUT_FILE)) {
			cout << __FUNCTION__ << " failed  :" << endl;
			return -1;
		}

		free_tree(root);
	}
	cout << __FUNCTION__ << "  total run time=" << tu.get_total_run_time() << "ms" << endl;

	return 0;
}

int TEST_inorderTraversal_iteratively()
{
	TimeUtil tu;

	if (0 != get_files("tree_traversal_test_data/inorder", &in_files, &out_files))
		return -1;
	for (int iii = 0; iii < in_files.size(); iii++) {
		const string in_file_name = in_files[iii];

		TreeNode *root;
		if (0 != create_tree(in_file_name, &root))
			return -1;

		// Run
		ofs.open(OUTPUT_FILE, fstream::out);
		tu.restart();

		inorderTraversal_iteratively(root);

		tu.stop();
		ofs.close();

		if (0 != compare_file(out_files[iii], OUTPUT_FILE)) {
			cout << __FUNCTION__ << " failed  :" << endl;
			return -1;
		}

		free_tree(root);
	}
	cout << __FUNCTION__ << "  total run time=" << tu.get_total_run_time() << "ms" << endl;

	return 0;
}

int TEST_postorderTraversal_recursively()
{
	TimeUtil tu;

	if (0 != get_files("tree_traversal_test_data/postorder", &in_files, &out_files))
		return -1;
	for (int iii = 0; iii < in_files.size(); iii++) {
		const string in_file_name = in_files[iii];

		TreeNode *root;
		if (0 != create_tree(in_file_name, &root))
			return -1;

		// Run
		ofs.open(OUTPUT_FILE, fstream::out);
		tu.restart();

		postorderTraversal_recursively(root);

		tu.stop();
		ofs.close();

		if (0 != compare_file(out_files[iii], OUTPUT_FILE)) {
			cout << __FUNCTION__ << " failed  :" << endl;
			return -1;
		}

		free_tree(root);
	}
	cout << __FUNCTION__ << "  total run time=" << tu.get_total_run_time() << "ms" << endl;

	return 0;
}

int TEST_postorderTraversal_iteratively()
{
	TimeUtil tu;

	if (0 != get_files("tree_traversal_test_data/postorder", &in_files, &out_files))
		return -1;
	for (int iii = 0; iii < in_files.size(); iii++) {
		const string in_file_name = in_files[iii];

		TreeNode *root;
		if (0 != create_tree(in_file_name, &root))
			return -1;

		// Run
		ofs.open(OUTPUT_FILE, fstream::out);
		tu.restart();

		postorderTraversal_iteratively(root);

		tu.stop();
		ofs.close();

		if (0 != compare_file(out_files[iii], OUTPUT_FILE)) {
			cout << __FUNCTION__ << " failed  :" << endl;
			return -1;
		}

		free_tree(root);
	}
	cout << __FUNCTION__ << "  total run time=" << tu.get_total_run_time() << "ms" << endl;

	return 0;
}

int main()
{
	TimeUtil tu;
	if (0 != TEST_preorderTraversal_recursively())
		return -1;

	if (0 != TEST_preorderTraversal_iteratively())
		return -1;

	if (0 != TEST_inorderTraversal_recursively())
		return -1;

	if (0 != TEST_inorderTraversal_iteratively())
		return -1;

	if (0 != TEST_postorderTraversal_recursively())
		return -1;

	if (0 != TEST_postorderTraversal_iteratively())
		return -1;

	cout << __FILE__ << "  total run time=" << tu.get_run_time() << "ms" << endl;

	return 0;
}
