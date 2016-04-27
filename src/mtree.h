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
    node_num(100), value_num(100)
  {}

  MTreeSetting(const int _max_height, const int _max_child_num,
               const int _node_num, const int _value_num)
               : max_height(_max_height), max_child_num(_max_child_num),
                 node_num(_node_num), value_num(_value_num)
  {}

  int max_height;
  int max_child_num;
  int node_num;
  int value_num;
};

void PrintMTreeNode(const MTreeNode* mnode);
void ClearMTree(MTreeNode* mnode);
void FreeMTree(MTreeNode* mnode);
MTreeNode* DeepCopyMTree(const MTreeNode* root);
MTreeNode* GenerateMTree(const MTreeSetting* const setting);

void CountSubtreeDiffValueCountMapReduce(MTreeNode* root);
void CountSubtreeDiffValueCountDivideAndConquer(MTreeNode* root);

bool DumpMTreeToFile(const MTreeNode* root, const std::string& file_path);
bool DumpMTreeToFile(const MTreeNode* root, const std::string& file_path,
                     const std::string& prefix_space);

bool CompareMTree(const MTreeNode* lhs, const MTreeNode* rhs);

#endif
