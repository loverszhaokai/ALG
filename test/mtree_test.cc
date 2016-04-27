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
 * This file contains the test of mtree
 */

#include <iostream>

#include "mtree.h"
#include "time_util.h"

//
// 1
//    2
//    3
static MTreeNode* CreateSimpleMTree() {
  MTreeNode* root = new MTreeNode();
  if (root == NULL) {
    return NULL;
  }
  root->value = 1;
  root->id = 1;

  MTreeNode* child_mnode = new MTreeNode();
  if (child_mnode == NULL) {
    return NULL;
  }
  child_mnode->value = 2;
  child_mnode->id = 2;
  child_mnode->parent = root;

  MTreeNode* child_next_mnode = new MTreeNode();
  if (child_next_mnode == NULL) {
    return NULL;
  }
  child_next_mnode->value = 3;
  child_next_mnode->id = 3;
  child_next_mnode->parent = root;

  root->child = child_mnode;
  child_mnode->next = child_next_mnode;

  return root;
}

static int test_simple()
{
  MTreeNode* simple_root = CreateSimpleMTree();
  CountSubtreeDiffValueCountMapReduce(simple_root);

  if (simple_root->subtree_diff_value_count != 3 ||
      simple_root->child->subtree_diff_value_count != 1 ||
      simple_root->child->next->subtree_diff_value_count != 1) {
    FreeMTree(simple_root);
    return -1;
  }

  ClearMTree(simple_root);
  CountSubtreeDiffValueCountDivideAndConquer(simple_root);

  if (simple_root->subtree_diff_value_count != 3 ||
      simple_root->child->subtree_diff_value_count != 1 ||
      simple_root->child->next->subtree_diff_value_count != 1) {
    FreeMTree(simple_root);
    return -1;
  }

  FreeMTree(simple_root);
	return 0;
}

static int test_complex()
{
  static struct TestInfo {
    MTreeSetting setting;
    int time_map_reduce;
    int time_divide_and_conquer;
  } test_infos [] = {
    { MTreeSetting(3, 3, 0, 10), -1, -1 },
    { MTreeSetting(5, 3, 0, 10), -1, -1 },
    { MTreeSetting(5, 5, 0, 10), -1, -1 },
    { MTreeSetting(5, 5, 0, 100), -1, -1 },
    { MTreeSetting(6, 5, 0, 100), -1, -1 },
    { MTreeSetting(6, 6, 0, 100), -1, -1 },
    { MTreeSetting(7, 5, 0, 100), -1, -1 },
    { MTreeSetting(8, 5, 0, 100), -1, -1 },
    { MTreeSetting(8, 5, 0, 50), -1, -1 },
    { MTreeSetting(8, 5, 0, 10), -1, -1 },
  };

  TimeUtil tu;

  for (int i = 0; i < sizeof(test_infos) / sizeof(test_infos[0]); i++) {

    std::cout << "\t case: #" << i + 1 << std::endl;
    std::cout << "\t\t max_height = " << test_infos[i].setting.max_height
      << "\t max_child_num = " << test_infos[i].setting.max_child_num
      << "\t min_value = " << test_infos[i].setting.min_value
      << "\t max_value = " << test_infos[i].setting.max_value << std::endl;

    MTreeNode* root_mnode = GenerateMTree(&test_infos[i].setting);
    if (root_mnode == NULL) {
      return -1;
    }
    MTreeNode* root_mnode_cp = DeepCopyMTree(root_mnode);
    if (root_mnode_cp == NULL) {
      return -1;
    }

    tu.restart();
    CountSubtreeDiffValueCountMapReduce(root_mnode);
    test_infos[i].time_map_reduce = tu.get_run_time();
    std::cout << "\t\t time_map_reduce         = " << test_infos[i].time_map_reduce << " ms" << std::endl;

    tu.restart();
    CountSubtreeDiffValueCountDivideAndConquer(root_mnode_cp);
    test_infos[i].time_divide_and_conquer = tu.get_run_time();
    std::cout << "\t\t time_divide_and_conquer = " << test_infos[i].time_divide_and_conquer << " ms" << std::endl;
    std::cout << std::endl;

    if (!CompareMTree(root_mnode, root_mnode_cp)) {
      std::cerr << "case: # " << i + 1 << " failed to CompareMTree()" << std::endl;
      return -1;
    }

    FreeMTree(root_mnode);
    FreeMTree(root_mnode_cp);
  }
	return 0;
}

int main()
{
	TimeUtil tu;

	if (test_simple() != 0) {
    std::cerr << "failed to test_simple()" << std::endl;
		return -1;
  }

  if (test_complex() != 0) {
    std::cerr << "failed to test_complex()" << std::endl;
    return -1;
  }

	std::cout << std::endl;
	std::cout << __FILE__ << "  total run time = " << tu.get_run_time()
		<< " ms" << std::endl;

	return 0;
}
