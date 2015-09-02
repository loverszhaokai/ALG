/*
   ALG
   --------------------------------

   Copyright 2015 Kai Zhao <loverszhao@gmail.com>

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   This file contains the struct TreeNode
 */

#ifndef _ALG_SRC_TREE_H_
#define _ALG_SRC_TREE_H_

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

#endif
