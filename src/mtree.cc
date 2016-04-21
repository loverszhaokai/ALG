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

#include <iostream>
#include <fstream>
#include <map>
#include <unordered_set>

#include "util/rand.h"

bool MTreeNode::operator == (const MTreeNode& rhs) const {
  //std::cout << "\t operator == ()" << std::endl;
  //PrintMTreeNode(this);
  //PrintMTreeNode(&rhs);

  if (this->id != rhs.id ||
    this->value != rhs.value ||
    this->subtree_diff_value_count != rhs.subtree_diff_value_count) {
    return false;
  }
  return true;
}

bool MTreeNode::operator != (const MTreeNode& rhs) const {
  //std::cout << "\t operator != ()" << std::endl;
  return !(this->operator == (rhs));
}

void PrintMTreeNode(const MTreeNode* mnode) {
  std::cout << "\t id=" << mnode->id << "\t value=" << mnode->value << "\t "
    << mnode->subtree_diff_value_count << std::endl;
}

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

static MTreeNode* DeepCopyMTreeRecursively(const MTreeNode* mnode,
                                           MTreeNode* parent_mnode) {
  MTreeNode* new_mnode = new MTreeNode();
  if (new_mnode == NULL) {
    return NULL;
  }
  *new_mnode = *mnode;
  new_mnode->parent = parent_mnode;

  if (mnode->child) {
    MTreeNode* child_mnode = DeepCopyMTreeRecursively(mnode->child, new_mnode);
    if (child_mnode == NULL) {
      return NULL;
    }
    new_mnode->child = child_mnode;
  }

  MTreeNode* next_mnode = mnode->next;
  MTreeNode* last_new_mnode = new_mnode;
  while (next_mnode) {
    MTreeNode* new_next_mnode = DeepCopyMTreeRecursively(next_mnode, parent_mnode);
    if (new_next_mnode == NULL) {
      return NULL;
    }
    last_new_mnode->next = new_next_mnode;
    last_new_mnode = new_next_mnode;
    next_mnode = next_mnode->next;
  }

  return new_mnode;
}

MTreeNode* DeepCopyMTree(const MTreeNode* root) {
  return DeepCopyMTreeRecursively(root, NULL);
}

static MTreeNode* GenerateMTreeRecursively(const MTreeSetting* const setting,
                                           MTreeNode* parent_mnode,
                                           const int max_height, int* id);

static bool GetChildNode(const MTreeSetting* const setting,
                         MTreeNode* parent_mnode,
                         const int max_height,
                         int* id) {
//std::cout << "\t" << __FUNCTION__ << "(max_height=" << max_height
//  << ", id=" << *id << ")" << std::endl;
  if (max_height > 1) {
    const int cnt_height = util::get_rand_int(0, max_height);
    //std::cout << "\t\t cnt_height=" << cnt_height << std::endl;
    if (cnt_height != 0) {
      // Have child node
      MTreeNode* child_mnode = GenerateMTreeRecursively(setting, parent_mnode, max_height - 1, id);
      if (child_mnode == NULL) {
        return false;
      }
      //std::cout << "\t id=" << parent_mnode->id << "\t child->id=" << child_mnode->id << std::endl;
      parent_mnode->child = child_mnode;
    }
  }
  return true;
}

static MTreeNode* GenerateMTreeRecursively(const MTreeSetting* const setting,
                                           MTreeNode* parent_mnode,
                                           const int max_height, int* id) {
//std::cout << "\t" << __FUNCTION__ << "(max_height=" << max_height
//  << ", id=" << *id << ")" << std::endl;
  MTreeNode* mnode = new MTreeNode();
  if (mnode == NULL) {
    return NULL;
  }

  mnode->id = (*id)++;
  mnode->value = util::get_rand_int(setting->min_value, setting->max_value);
  //std::cout << "id=" << *id << "\t max_height = " << max_height << std::endl;
  mnode->parent = const_cast<MTreeNode*>(parent_mnode);

  if (!GetChildNode(setting, mnode, max_height, id)) {
    return NULL;
  }

  const int sibling_num = util::get_rand_int(0, setting->max_child_num);
  //std::cout << "id=" << *id << "\t sibling_num=" << sibling_num << std::endl;
  MTreeNode* last_mnode = mnode;
  for (int i = 0; i < sibling_num; i++) {
    MTreeNode* cnt_mnode = new MTreeNode();
    if (cnt_mnode == NULL) {
      return NULL;
    }
    cnt_mnode->id = (*id)++;
    cnt_mnode->value = util::get_rand_int(setting->min_value, setting->max_value);
    //std::cout << "id=" << cnt_mnode->id << "\t max_height = " << max_height << std::endl;
    //std::cout << "\t id=" << mnode->id << "\t sibling_node->id=" << cnt_mnode->id << std::endl;
    cnt_mnode->parent = const_cast<MTreeNode*>(parent_mnode);

    if (!GetChildNode(setting, cnt_mnode, max_height, id)) {
      return NULL;
    }

    last_mnode->next = cnt_mnode;
    last_mnode = cnt_mnode;
  }

  return mnode;
}

MTreeNode* GenerateMTree(const MTreeSetting* const setting) {
  MTreeNode* root = new MTreeNode();
  if (root == NULL) {
    return NULL;
  }
  root->id = 0;
  root->value = util::get_rand_int(setting->min_value, setting->max_value);

  int id = 1;
  MTreeNode* child = GenerateMTreeRecursively(setting, root, setting->max_height, &id);
  if (child == NULL) {
    return NULL;
  }
  root->child = child;

  return root;
}

static void GatherParentMTreeNodes(
  MTreeNode* mnode,
  std::map<int, std::unordered_set<MTreeNode*> >* value_nodes) {

  const int val = mnode->value;
  while (mnode) {
    (*value_nodes)[val].insert(mnode);
    mnode = mnode->parent;
  }
}

static void CountSubtreeDiffValueCountMapReduceRecursively(
  MTreeNode* mnode,
  std::map<int, std::unordered_set<MTreeNode*> >* value_nodes) {

  while (mnode) {
    GatherParentMTreeNodes(mnode, value_nodes);
    CountSubtreeDiffValueCountMapReduceRecursively(mnode->child, value_nodes);
    mnode = mnode->next;
  }
}

void CountSubtreeDiffValueCountMapReduce(MTreeNode* root) {

  std::map<int, std::unordered_set<MTreeNode*> > value_nodes;

  CountSubtreeDiffValueCountMapReduceRecursively(root, &value_nodes);

  for (auto it = value_nodes.begin(); it != value_nodes.end(); it++) {
    for (auto item : it->second) {
      item->subtree_diff_value_count++;
    }
  }
}

static void CountSubtreeDiffValueCountDivideAndConquerRecursively(
  MTreeNode* mnode, std::unordered_set<int>* parent_values) {

  while (mnode) {

    std::unordered_set<int> self_values;
    self_values.insert(mnode->value);
    CountSubtreeDiffValueCountDivideAndConquerRecursively(mnode->child, &self_values);

    mnode->subtree_diff_value_count = self_values.size();
    parent_values->insert(self_values.begin(), self_values.end());

    mnode = mnode->next;
  }
}

void CountSubtreeDiffValueCountDivideAndConquer(MTreeNode* root) {
  std::unordered_set<int> self_values;
  CountSubtreeDiffValueCountDivideAndConquerRecursively(root, &self_values);
  root->subtree_diff_value_count = self_values.size();
}

static int GetChildNum(const MTreeNode* mnode) {
//std::cout << "\tGetChildNum(mnode->id=" << mnode->id << ")" << std::endl;
  int child_num = 0;
  const MTreeNode* child_mnode = mnode->child;
  while (child_mnode) {
  //std::cout << "\t\tchild->id=" << child_mnode->id << std::endl;
    child_num++;
    child_mnode = child_mnode->next;
  }
  return child_num;
}

static void DumpMTreeToFileRecusively(const MTreeNode* mnode, std::fstream& fs) {
  if (mnode == NULL) {
    return;
  }

  fs << "id=" << mnode->id << "\tvalue=" << mnode->value
    << "\t  subtree_diff_value_count=" << mnode->subtree_diff_value_count
    << "\tchild_num=" << GetChildNum(mnode) << std::endl;

  fs << "\tDump Child of mnode->id=" << mnode->id << std::endl;
  DumpMTreeToFileRecusively(mnode->child, fs);

  fs << "\n";

  if (mnode->parent && mnode != mnode->parent->child) {
    return;
  }
  const MTreeNode* next_mnode = mnode->next;
  while (next_mnode) {
    fs << "\tDump Next of next_mnode->id=" << next_mnode->id << std::endl;
    DumpMTreeToFileRecusively(next_mnode, fs);
    next_mnode = next_mnode->next;
  }
}

bool DumpMTreeToFile(const MTreeNode* root, const std::string& file_path) {
  std::fstream fs(file_path.c_str(), std::fstream::out);
  if (!fs.is_open()) {
    std::cerr << "failed to open:" << file_path << "||" << std::endl;
    return false;
  }

  DumpMTreeToFileRecusively(root, fs);

  fs.close();
  return true;
}

bool CompareMTree(const MTreeNode* lhs, const MTreeNode* rhs) {
  if (lhs == NULL && rhs == NULL) {
    return true;
  }

  if (lhs == NULL || rhs == NULL) {
    return false;
  }
  //std::cout << "CompareMTree(lhs->id=" << lhs->id << ")" << std::endl;

  if (*lhs != *rhs) {
    return false;
  }

  if (!CompareMTree(lhs->child, rhs->child)) {
    return false;
  }

  if (lhs->parent && lhs->parent->child != lhs) {
    // lhs is not first child
    return true;
  }

  const MTreeNode* lhs_child_mnode = lhs->next;
  const MTreeNode* rhs_child_mnode = rhs->next;

  while (lhs_child_mnode && rhs_child_mnode) {
    if (!CompareMTree(lhs_child_mnode, rhs_child_mnode)) {
      return false;
    }
    lhs_child_mnode = lhs_child_mnode->next;
    rhs_child_mnode = rhs_child_mnode->next;
  }

  if (lhs_child_mnode || rhs_child_mnode) {
    return false;
  }

  return true;
}

