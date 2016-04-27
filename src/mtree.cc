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
#include <unordered_map>

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

  if (mnode->parent && mnode->parent->child != mnode) {
    return new_mnode;
  }

  // Traverse the sibling once
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
  MTreeNode* root_parent = new MTreeNode();
  MTreeNode* root_tmp = const_cast<MTreeNode*>(root);
  root_tmp->parent = root_parent;
  root_parent->child = root_tmp;

  MTreeNode* new_root = DeepCopyMTreeRecursively(root_tmp, NULL);

  root_tmp->parent = NULL;
  delete root_parent;

  return new_root;
}

static MTreeNode* GenerateMTreeRecursively(const MTreeSetting* const setting,
                                           MTreeNode* parent_mnode,
                                           const int max_height, int* id,
                                           std::fstream& fs);

static bool GetChildNode(const MTreeSetting* const setting,
                         MTreeNode* parent_mnode,
                         const int max_height,
                         int* id, std::fstream& fs) {
//std::cout << "\t" << __FUNCTION__ << "(max_height=" << max_height
//  << ", id=" << *id << ")" << std::endl;
  if (max_height <= 1) {
    return true;
  }

  const int cnt_height = util::get_rand_int(0, max_height);
  //std::cout << "\t\t cnt_height=" << cnt_height << std::endl;
  if (cnt_height != 0) {
    // Have child node
    MTreeNode* child_mnode = GenerateMTreeRecursively(setting, parent_mnode, max_height - 1, id, fs);
    if (child_mnode == NULL) {
      return false;
    }
    //std::cout << "\t id=" << parent_mnode->id << "\t child->id=" << child_mnode->id << std::endl;
    parent_mnode->child = child_mnode;
  }
  return true;
}

static MTreeNode* GenerateMTreeRecursively(const MTreeSetting* const setting,
                                           MTreeNode* parent_mnode,
                                           const int max_height, int* id,
                                           std::fstream& fs) {
//std::cout << "\t" << __FUNCTION__ << "(max_height=" << max_height
//  << ", id=" << *id << ")" << std::endl;
  MTreeNode* mnode = new MTreeNode();
  if (mnode == NULL) {
    return NULL;
  }

  mnode->id = (*id)++;
  mnode->value = util::get_rand_int(setting->min_value, setting->max_value);
  //fs << "id=" << mnode->id << std::endl;
  //std::cout << "id=" << mnode->id << "\t max_height = " << max_height << std::endl;
  mnode->parent = const_cast<MTreeNode*>(parent_mnode);

  if (!GetChildNode(setting, mnode, max_height, id, fs)) {
    return NULL;
  }

  const int sibling_num = util::get_rand_int(0, setting->max_child_num);
  //std::cout << "id=" << mnode->id << "\t sibling_num=" << sibling_num << std::endl;
  MTreeNode* last_mnode = mnode;
  for (int i = 0; i < sibling_num; i++) {
    MTreeNode* cnt_mnode = new MTreeNode();
    if (cnt_mnode == NULL) {
      return NULL;
    }
    cnt_mnode->id = (*id)++;
    cnt_mnode->value = util::get_rand_int(setting->min_value, setting->max_value);
    //fs << "id=" << cnt_mnode->id << std::endl;
    //std::cout << "id=" << cnt_mnode->id << "\t max_height = " << max_height << std::endl;
    //std::cout << "\t id=" << mnode->id << "\t sibling_node->id=" << cnt_mnode->id << std::endl;
    cnt_mnode->parent = const_cast<MTreeNode*>(parent_mnode);

    if (!GetChildNode(setting, cnt_mnode, max_height, id, fs)) {
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

  const std::string file_path = "generate_mtree.log";
  std::fstream fs(file_path.c_str(), std::fstream::out);
  if (!fs.is_open()) {
    std::cerr << "failed to open:" << file_path << "||" << std::endl;
    return NULL;
  }

  int id = 1;
  MTreeNode* child = GenerateMTreeRecursively(setting, root, setting->max_height, &id, fs);
  if (child == NULL) {
    fs.close();
    return NULL;
  }
  root->child = child;

  fs << "\t Finish to generate mtree\n";

  fs.close();
  return root;
}

static void CountSubtreeDiffValueCountMapReduceRecursively(
    MTreeNode* mnode,
  std::unordered_map<int, std::unordered_set<int> >* value_nodes) {
  while (mnode) {
    const int val = mnode->value;
    std::unordered_set<int>& set = (*value_nodes)[val];
    set.insert(mnode->id);
    mnode->subtree_diff_value_count++;

    MTreeNode* parent = mnode->parent;
    while (parent) {
      if (set.find(parent->id) != set.end()) {
        break;
      } else {
        set.insert(parent->id);
        parent->subtree_diff_value_count++;
      }
      parent = parent->parent;
    }
    CountSubtreeDiffValueCountMapReduceRecursively(mnode->child, value_nodes);
    mnode = mnode->next;
  }
}

void CountSubtreeDiffValueCountMapReduce(MTreeNode* root) {
  std::unordered_map<int, std::unordered_set<int> > value_nodes;
  CountSubtreeDiffValueCountMapReduceRecursively(root, &value_nodes);
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
  if (mnode == NULL) {
    return 0;
  }

  int child_num = 0;
  const MTreeNode* child_mnode = mnode->child;
  while (child_mnode) {
    child_num++;
    child_mnode = child_mnode->next;
  }

  return child_num;
}

static void DumpMTreeToFileRecusively(const MTreeNode* mnode, std::fstream& fs) {
  if (mnode == NULL) {
    return;
  }

  fs << mnode->id << " " << mnode->value << " "
    << mnode->subtree_diff_value_count << " "
    << GetChildNum(mnode) << std::endl;

  DumpMTreeToFileRecusively(mnode->child, fs);

  if (mnode->parent && mnode != mnode->parent->child) {
    return;
  }
  const MTreeNode* next_mnode = mnode->next;
  while (next_mnode) {
    DumpMTreeToFileRecusively(next_mnode, fs);
    next_mnode = next_mnode->next;
  }
}

static void DumpMTreeToFileRecusively(const MTreeNode* mnode, std::fstream& fs,
                                      const std::string& prefix_space) {
  if (mnode == NULL) {
    return;
  }

  fs << prefix_space;

  if (mnode->parent) {
    fs << "[" << mnode->parent->id << "]-> ";
  }

  fs << mnode->id << " " << mnode->value << " "
    << mnode->subtree_diff_value_count << " "
    << GetChildNum(mnode) << std::endl;

  DumpMTreeToFileRecusively(mnode->child, fs, prefix_space + "     ");

  if (mnode->parent && mnode != mnode->parent->child) {
    return;
  }
  const MTreeNode* next_mnode = mnode->next;
  while (next_mnode) {
    DumpMTreeToFileRecusively(next_mnode, fs, prefix_space);
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

bool DumpMTreeToFile(const MTreeNode* root, const std::string& file_path,
                     const std::string& prefix_space) {
  std::fstream fs(file_path.c_str(), std::fstream::out);
  if (!fs.is_open()) {
    std::cerr << "failed to open:" << file_path << "||" << std::endl;
    return false;
  }

  DumpMTreeToFileRecusively(root, fs, prefix_space);

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

