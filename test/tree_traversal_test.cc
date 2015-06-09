#include "tree_traversal.h"

#include <stdio.h>

#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

#include "test.h"
#include "tree.h"

using std::cout;
using std::endl;
using std::fstream;
using std::queue;
using std::string;
using std::stringstream;

extern fstream ofs;

vector<string> in_files, out_files;

int str_to_int(const string &_str)
{
	stringstream ss(_str);
	int val;
	ss >> val;
	return val;
}

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
}

void dump_tree()
{
}

int TEST_preorderTraversal_recursively()
{
	if (0 != get_files("tree_traversal_test_data/preorder", &in_files, &out_files))
		return -1;
	for (int iii = 0; iii < in_files.size(); iii++) {
		const string in_file_name = in_files[iii];
		ofs.open(OUTPUT_FILE, fstream::out);
		TreeNode *root;
		if (0 != create_tree(in_file_name, &root))
			return -1;
		preorderTraversal_recursively(root);
		if (0 != compare_file(out_files[iii], OUTPUT_FILE)) {
			cout << "failed  :" << endl;
			cout << "expected:" << out_files[iii] << endl;
			cout << "actual  :" << OUTPUT_FILE << endl;
			return -1;
		}
		ofs.close();
	}

	return 0;
}

int main()
{
	if (0 != TEST_preorderTraversal_recursively())
		return -1;
	return 0;
}
