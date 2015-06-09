#ifndef _ALG_SRC_TREE_H_
#define _ALG_SRC_TREE_H_

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

#endif
