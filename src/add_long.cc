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
 * This file contains the add functions when the integer is very long
 */

#include "add_long.h"

// Reverse a list
// E.g. 1->2->3 after reverse is: 3->2->1
static ListNode *reverse(ListNode *head)
{
	ListNode *pre_node = NULL, *next_node;

	while (head) {

		next_node = head->next;

		head->next = pre_node;

		pre_node = head;

		head = next_node;

	}

	return pre_node;
}

ListNode *add_long(ListNode *head1, ListNode *head2)
{
	if (head1 == NULL && head2 == NULL)
		return NULL;

	// Reverse head1 and head2
	head1 = reverse(head1);
	head2 = reverse(head2);

	ListNode *orig_head1 = head1;
	ListNode *orig_head2 = head2;

	ListNode pseudo_head(0); // pseudo_head.next is the real head
	ListNode *pre_node = &pseudo_head;
	ListNode *node;
	int carry = 0;

	while (head1 && head2) {

		carry += head1->val + head2->val;

		node = new ListNode(carry % 10);

		carry /= 10;
		pre_node->next = node;
		pre_node = node;

		head1 = head1->next;
		head2 = head2->next;
	}

	while (head1) {

		carry += head1->val;

		node = new ListNode(carry % 10);

		carry /= 10;
		pre_node->next = node;
		pre_node = node;

		head1 = head1->next;
	}

	while (head2) {

		carry += head2->val;

		node = new ListNode(carry % 10);

		carry /= 10;
		pre_node->next = node;
		pre_node = node;

		head2 = head2->next;
	}

	if (carry != 0) {

		node = new ListNode(carry % 10);
		pre_node->next = node;
	}

	// Reverse head1 and head2
	reverse(orig_head1);
	reverse(orig_head2);

	// pseudo_head.next is the real head
	return reverse(pseudo_head.next);
}
