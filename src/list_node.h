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
 * This file contains the functions of ListNode
 */

#ifndef _ALG_SRC_LIST_NODE_H_
#define _ALG_SRC_LIST_NODE_H_

#include <stdlib.h>

#include <vector>

using std::vector;

struct ListNode {

	int val;
	ListNode *next;

	ListNode(int _v) : val(_v) { next = NULL; }
};

// Create a list where each value of the node is equal to the correspondingly
// value in nums
//
// E.g. nums = { 1, 2, 3, 4, 5 };
// ListNode *head = 1->2->3->4->5
//
ListNode *create_list(const vector<int> &nums);

// Free a list including all nodes linked by next
void free_list(ListNode *head);

// Compare two list, return 0 if all the values of lhs and rhs are the same
// Otherwise, return -1
int cmp_list(ListNode *lhs, ListNode *rhs);

void print_list(ListNode *head);

#endif
