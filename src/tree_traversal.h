#ifndef _ALG_STC_TREE_TRAVERSAL_H_
#define _ALG_STC_TREE_TRAVERSAL_H_

struct TreeNode;

void preorderTraversal_recursively(TreeNode *root);
void preorderTraversal_iteratively(TreeNode *root);

void inorderTraversal_recursively(TreeNode *root);
void inorderTraversal_iteratively(TreeNode *root);

void postorderTraversal_recursively(TreeNode *root);
void postorderTraversal_iteratively(TreeNode *root);

#endif
