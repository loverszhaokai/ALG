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

#include <string>

struct MTreeNode {

  MTreeNode() : id(0), value(0), subtree_diff_value_count(0),
    parent(nullptr), child(nullptr), next(nullptr)
  {}

  int id;
  int value;
  int subtree_diff_value_count;

  struct MTreeNode* parent;
  struct MTreeNode* child;
  struct MTreeNode* next;

  bool operator == (const MTreeNode& rhs) const;
  bool operator != (const MTreeNode& rhs) const;
};

struct MTreeSetting {
  MTreeSetting() : max_height(10), max_child_num(10),
    min_value(0), max_value(100)
  {}

  MTreeSetting(const int _max_height, const int _max_child_num,
               const int _min_value, const int _max_value)
               : max_height(_max_height), max_child_num(_max_child_num),
                 min_value(_min_value), max_value(_max_value)
  {}

  int max_height;
  int max_child_num;
  int min_value;
  int max_value;
};

void PrintMTreeNode(const MTreeNode* mnode);
void ClearMTree(MTreeNode* mnode);
void FreeMTree(MTreeNode* mnode);
MTreeNode* DeepCopyMTree(const MTreeNode* root);
MTreeNode* GenerateMTree(const MTreeSetting* const setting);

void CountSubtreeDiffValueCountMapReduce(MTreeNode* root);
void CountSubtreeDiffValueCountDivideAndConquer(MTreeNode* root);

bool DumpMTreeToFile(const MTreeNode* root, const std::string& file_path);

bool CompareMTree(const MTreeNode* lhs, const MTreeNode* rhs);

#endif
