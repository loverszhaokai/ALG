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
 * This file contains the struct MTreeNode
 */

#include "mtree.h"

void ClearMTree(MTreeNode* mnode) {
  while (mnode) {
    mnode->subtree_diff_value_count = 0;
    ClearMTree(mnode->child);
    mnode = mnode->next;
  }
}

void FreeMTree(MTreeNode* mnode) {
  while (mnode) {
    FreeMTree(mnode->child);
    delete mnode;
    mnode = mnode->next;
  }
}

MTreeNode* GenerateMTree(const int id, const int max_height,
                         const int max_child_num, const int min_value,
                         const int max_value) {
  MTreeNode* mnode = new MTreeNode();
}
