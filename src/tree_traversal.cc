/*
 * ALG
 * --------------------------------
 *
 * Copyright 2016 Kai Zhao <loverszhao@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * This file contains the tree traversal algorithms, including recursively
 * and iteratively
 */

#include "tree_traversal.h"

#include <stdio.h>

#include <fstream>
#include <iostream>
#include <stack>

#include "tree.h"

using std::endl;
using std::fstream;
using std::stack;

extern fstream ofs;

void preorderTraversal_recursively(TreeNode *root)
{
	if (NULL != root) {
		ofs << root->val << endl;
		preorderTraversal_recursively(root->left);
		preorderTraversal_recursively(root->right);
	}
}

void preorderTraversal_iteratively(TreeNode *root)
{
	TreeNode *node = root;
	stack<TreeNode *> nodes;
	while (node) {
		ofs << node->val << endl;
		nodes.push(node);
		node = node->left;
	}
	while (!nodes.empty()) {
		TreeNode *node = nodes.top();
		nodes.pop();
		node = node->right;
		while (node) {
			ofs << node->val << endl;
			nodes.push(node);
			node = node->left;
		}
	}
}

void inorderTraversal_recursively(TreeNode *root)
{
	if (NULL != root) {
		inorderTraversal_recursively(root->left);
		ofs << root->val << endl;
		inorderTraversal_recursively(root->right);
	}
}

void inorderTraversal_iteratively(TreeNode *root)
{
	stack<TreeNode *> nodes;
	TreeNode *node = root;
	while (node) {
		nodes.push(node);
		node = node->left;
	}
	while (!nodes.empty()) {
		node = nodes.top();
		ofs << node->val << endl;
		nodes.pop();

		node = node->right;
		while (node) {
			nodes.push(node);
			node = node->left;
		}
	}
}

void postorderTraversal_recursively(TreeNode *root)
{
	if (NULL != root) {
		postorderTraversal_recursively(root->left);
		postorderTraversal_recursively(root->right);
		ofs << root->val << endl;
	}
}

void postorderTraversal_iteratively(TreeNode *root)
{
	if (NULL == root)
		return;

	TreeNode *node = root;
	stack<TreeNode *> nodes;
	
	while (node) {
		nodes.push(node);
		node = node->left;
	}

	TreeNode *pre_node = NULL;
	while (!nodes.empty()) {
		node = nodes.top();

		if (NULL == node->right || pre_node == node->right) {
			ofs << node->val << endl;
			pre_node = node;
			nodes.pop();
		} else {
			node = node->right;
			while (node) {
				nodes.push(node);
				node = node->left;
			}
		}
	}
}
