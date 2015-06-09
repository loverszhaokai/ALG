#include "tree_traversal.h"

#include <stdio.h>

#include <fstream>
#include <iostream>

#include "tree.h"

using std::endl;
using std::fstream;

extern fstream ofs;

void preorderTraversal_recursively(TreeNode *root)
{
	if (NULL != root) {
		ofs << root->val << endl;
		preorderTraversal_recursively(root->left);
		preorderTraversal_recursively(root->right);
	}
}
