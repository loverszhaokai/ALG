/*
 * ALG
 * --------------------------------
 *
 * Copyright 2015 Kai Zhao
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * This file contains the functions of ListNode
 */

#include "list_node.h"

#include <stdio.h>

ListNode *create_list(const vector<int> &nums)
{
	if (nums.size() == 0)
		return NULL;

	ListNode *head = new ListNode(nums[0]);
	ListNode *pre_node = head, *node;

	for (int iii = 1; iii < nums.size(); iii++) {

		node = new ListNode(nums[iii]);
		pre_node->next = node;
		pre_node = node;

	}

	return head;
}

void free_list(ListNode *head)
{
	ListNode *next_node;

	while (head) {

		next_node = head->next;

		free(head);

		head = next_node;
	}
}

int cmp_list(ListNode *lhs, ListNode *rhs)
{
	if (lhs == NULL && rhs == NULL)
		return 0;

	if (lhs == NULL || rhs == NULL)
		return -1;

	while (lhs && rhs) {

		if (lhs->val != rhs->val)
			return -1;

		lhs = lhs->next;
		rhs = rhs->next;
	}

	if (lhs || rhs)
		return -1;

	return 0;
}

void print_list(ListNode *head)
{
	printf("Print list:\n\t");

	while (head) {
		printf("%d", head->val);
		head = head->next;
		if (head)
			printf("-> ");
	}
	printf("\n");
}
