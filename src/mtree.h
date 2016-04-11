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


#ifndef _ALG_SRC_MTREE_H_
#define _ALG_SRC_MTREE_H_

struct MTreeNode {

  struct MTreeNode() : id(0), value(0), subtree_diff_value_count(0),
                       parent(NULL), child(NULL), next(NULL)
  {}

  int id;
  int value;
  int subtree_diff_value_count;

  struct MTreeNode* parent;
  struct MTreeNode* child;
  struct MTreeNode* next;
};

#endif
