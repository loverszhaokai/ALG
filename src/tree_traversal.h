/*
 * ALG
 * --------------------------------
 *
 * Copyright 2015 Kai Zhao
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

#ifndef _ALG_SRC_TREE_TRAVERSAL_H_
#define _ALG_SRC_TREE_TRAVERSAL_H_

struct TreeNode;

void preorderTraversal_recursively(TreeNode *root);
void preorderTraversal_iteratively(TreeNode *root);

void inorderTraversal_recursively(TreeNode *root);
void inorderTraversal_iteratively(TreeNode *root);

void postorderTraversal_recursively(TreeNode *root);
void postorderTraversal_iteratively(TreeNode *root);

#endif
