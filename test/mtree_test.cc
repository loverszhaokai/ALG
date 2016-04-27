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

#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

#include "mtree.h"
#include "test.h"
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

struct ElementInfo {
  int child_index;
  int child_num;
  MTreeNode* parent_mnode;
  MTreeNode* prev_sibling_mnode;
};

static MTreeNode* CreateOneMTreeNode(const std::string& line, ElementInfo* einfo) {
  MTreeNode* mnode = new MTreeNode();
  if (mnode == NULL) {
    return NULL;
  }

  std::stringstream ss(line);
  int id, value, subtree_diff_value_count, child_num;
  ss >> id >> value >> subtree_diff_value_count >> child_num;

  mnode->id = id;
  mnode->value = value;
  mnode->subtree_diff_value_count = subtree_diff_value_count;
  mnode->parent = NULL;
  mnode->child = NULL;
  mnode->next = NULL;

  einfo->child_num = child_num;

  return mnode;
}


static MTreeNode* CreateMTreeNode(const std::string& file_name) {
	std::fstream ifs(file_name.c_str(), std::fstream::in);
	if (!ifs) {
		std::cerr << "failed to open(" << file_name << ")\n";
		return NULL;
	}

  std::string line;
  MTreeNode root_parent_mnode;
  root_parent_mnode.child = NULL;
  
  std::stack<ElementInfo> elements;
  ElementInfo element_info;
  element_info.child_index = 1; 
  element_info.child_num = 1; 
  element_info.parent_mnode = &root_parent_mnode;
  element_info.prev_sibling_mnode = NULL;
  elements.push(element_info); // root node

  ElementInfo* cnt_element = &elements.top();

  while (!elements.empty()) {
    cnt_element = &elements.top();
    if (cnt_element->child_index > cnt_element->child_num) {
      elements.pop();
      continue;
    }

    if (!std::getline(ifs, line)) {
      return NULL;
    }

    MTreeNode* mnode = CreateOneMTreeNode(line, &element_info);
    if (mnode == NULL) {
      return NULL;
    }

    mnode->parent = cnt_element->parent_mnode;

    if (cnt_element->prev_sibling_mnode != NULL) {
      cnt_element->prev_sibling_mnode->next = mnode;
    } else {
      cnt_element->parent_mnode->child = mnode;
    }
    cnt_element->prev_sibling_mnode = mnode;
    cnt_element->child_index++;

    if (element_info.child_num > 0) {
      element_info.child_index = 1;
      element_info.parent_mnode = mnode;
      elements.push(element_info);
    }
  }

  return root_parent_mnode.child;
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

static int test_generate()
{
  static struct TestInfo {
    MTreeSetting setting;
    int time_map_reduce;
    int time_divide_and_conquer;
  } test_infos [] = {
    { MTreeSetting(5, 5, 10000, 1000), -1, -1 },
    { MTreeSetting(5, 5, 10000, 10000), -1, -1 },
    { MTreeSetting(5, 5, 10000, 100000), -1, -1 },

    { MTreeSetting(5, 5, 100000, 10000), -1, -1 },
    { MTreeSetting(5, 5, 100000, 100000), -1, -1 },
    { MTreeSetting(5, 5, 100000, 1000000), -1, -1 },

    { MTreeSetting(5, 5, 1000000, 100000), -1, -1 },
    { MTreeSetting(5, 5, 1000000, 1000000), -1, -1 },
    { MTreeSetting(5, 5, 1000000, 10000000), -1, -1 },

    { MTreeSetting(10, 10, 10000, 1000), -1, -1 },
    { MTreeSetting(10, 10, 10000, 10000), -1, -1 },
    { MTreeSetting(10, 10, 10000, 100000), -1, -1 },

    { MTreeSetting(10, 10, 100000, 10000), -1, -1 },
    { MTreeSetting(10, 10, 100000, 100000), -1, -1 },
    { MTreeSetting(10, 10, 100000, 1000000), -1, -1 },

    { MTreeSetting(10, 10, 1000000, 100000), -1, -1 },
    { MTreeSetting(10, 10, 1000000, 1000000), -1, -1 },
    { MTreeSetting(10, 10, 1000000, 10000000), -1, -1 },
  };

  TimeUtil tu;

  for (int i = 0; i < sizeof(test_infos) / sizeof(test_infos[0]); i++) {

    std::cout << "\t case: #" << i + 1 << std::endl;
    std::cout << "\t\t max_height = " << test_infos[i].setting.max_height
      << "\t max_child_num = " << test_infos[i].setting.max_child_num
      << "\t node_num = " << test_infos[i].setting.node_num
      << "\t value_num = " << test_infos[i].setting.value_num << std::endl;

    MTreeNode* root_mnode = GenerateMTree(&test_infos[i].setting);
    if (root_mnode == NULL) {
      return -1;
    }

    char file_path_buf[100];
    snprintf(file_path_buf, sizeof(file_path_buf), "complex_%d.output", i + 1);

    if (!DumpMTreeToFile(root_mnode, file_path_buf)) {
      return -1;
    }

    MTreeNode* root_parse = CreateMTreeNode(file_path_buf);
    if (!CompareMTree(root_mnode, root_parse)) {
      std::cerr << "case: # " << i + 1 << " failed to CompareMTree()" << std::endl;
      return -1;
    }
    FreeMTree(root_parse);


    snprintf(file_path_buf, sizeof(file_path_buf), "complex_%d_h.output", i + 1);
    if (!DumpMTreeToFile(root_mnode, file_path_buf, "")) {
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

static int test_parse()
{
  TimeUtil tu;
  std::vector<std::string> in_files, out_files;
	if (0 != get_files("test/mtree_test_data/", &in_files, &out_files)) {
    return -1;
  }

  for (int i = 0; i < in_files.size(); i++) {
    std::cout << "\t case: #" << i + 1 << std::endl;
    MTreeNode* root_mnode = CreateMTreeNode(in_files[i]);
    if (root_mnode == NULL) {
      return -1;
    }

    MTreeNode* root_mnode_cp = DeepCopyMTree(root_mnode);
    if (root_mnode_cp == NULL) {
      return -1;
    }

    tu.restart();
    CountSubtreeDiffValueCountMapReduce(root_mnode);
    int run_time = tu.get_run_time();
    std::cout << "\t\t time_map_reduce         = " << run_time << " ms" << std::endl;

    tu.restart();
    CountSubtreeDiffValueCountDivideAndConquer(root_mnode_cp);
    run_time = tu.get_run_time();
    std::cout << "\t\t time_divide_and_conquer = " << run_time << " ms" << std::endl;
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

  if (test_parse() != 0) {
    std::cerr << "failed to test_complex()" << std::endl;
    return -1;
  }

	std::cout << std::endl;
	std::cout << __FILE__ << "  total run time = " << tu.get_run_time()
		<< " ms" << std::endl;

	return 0;
}
