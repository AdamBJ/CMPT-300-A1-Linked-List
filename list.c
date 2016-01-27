/*
 * list.c
 *
 *  Created on: Jan 19, 2016
 *      Author: ubuntu
 */
#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include <stdbool.h>
#include <string.h>
#include <assert.h>

/*
 * Allocate memory for a node of type struct nodeStruct and initialize
 * it with the value item. Return a pointer to the new node.
 */
struct nodeStruct* List_createNode(int item) {
	struct nodeStruct* newNode = malloc(sizeof(struct nodeStruct));

	if (newNode == 0) {
		printf("ERROR: Insufficient memory");
		return NULL;
	}

	newNode -> item = item;
	newNode -> next = NULL;

	return newNode;
}

/*Checks if the node is already in the list and rejects. We check for the
 * node object itself, not the item stored inside it.*/
int List_nodeAlreadyInserted(struct nodeStruct *headRef, struct nodeStruct *node) {
	struct nodeStruct *curr = headRef;

	while(curr != NULL) {
		if (curr == node)
			return 1;
		curr = curr -> next;
	}

	return 0;
}

/*
 * Insert node at the head of the list.
 */
void List_insertHead (struct nodeStruct **headRef, struct nodeStruct *node) {
	/*If node is a null pointer or node is already present in the list we return
	 * without inserting anything.*/
	if (node == NULL || List_nodeAlreadyInserted(*headRef, node))
		return;

	node -> next = *headRef;
	*headRef = node;
}

/*
 * Insert node after the tail of the list.
 */
void List_insertTail (struct nodeStruct **headRef, struct nodeStruct *node) {
	if (node == NULL || List_nodeAlreadyInserted(*headRef, node))
		return;

	struct nodeStruct* temp = *headRef;

	while (temp -> next != NULL) {
		temp = temp -> next;
	}

	temp -> next = node;
}

/*
 * Count number of nodes in the list.
 * Return 0 if the list is empty, i.e., head == NULL
 */
int List_countNodes (struct nodeStruct *head) {
	int count = 0;
	struct nodeStruct* temp = head;

	while (temp != NULL) {
		temp = temp -> next;
		count++;
	}

	return count;
}

/*
 * Return the first node holding the value item, return NULL if none found
 */
struct nodeStruct* List_findNode(struct nodeStruct *head, int item) {
	struct nodeStruct* temp = head;

	while (temp != NULL) {
		if (temp -> item == item)
			return temp;
		temp = temp -> next;
	}

	return NULL;
}

/*
 * Delete node from the list and free memory allocated to it.
 * This function assumes that node has been properly set to a valid node
 * in the list. For example, the client code may have found it by calling
 * List_findNode(). If the list contains only node, the head of the list
 * should be set to NULL.
 */
void List_deleteNode (struct nodeStruct **headRef, struct nodeStruct *node) {
	struct nodeStruct *prev, *curr;
	prev = curr = *headRef;

	/*We assume that the node exists.*/
	while (curr != node) {
		prev = curr;
		curr = curr -> next;
	}

	if (curr == *headRef)
		*headRef = curr -> next;

	/*We've got the node to delete*/
	prev -> next = curr -> next;
	free(curr);
}

/*
 * Sort the list in ascending order based on the item field.
 * Any sorting algorithm is fine.
 */
void List_sort (struct nodeStruct **headRef) {
	if (*headRef == NULL)
		return;

	struct nodeStruct *sortedHeadRef = NULL;
	struct nodeStruct *currRef, *currMaxNodeRef;
	currRef = currMaxNodeRef = *headRef;

	int numElems = List_countNodes(*headRef);
	for (int i = 0; i < numElems; i++) {
		/*Scan through the list to find the maximal element. Insert it
		 * into the sorted list.*/
		while (currRef != NULL) {
			if ((currRef -> item) > (currMaxNodeRef -> item))
				currMaxNodeRef = currRef;
			currRef = currRef -> next;
		}

		List_insertHead(&sortedHeadRef, List_createNode(currMaxNodeRef -> item));
		List_deleteNode(headRef, currMaxNodeRef);

		currRef = *headRef;
		currMaxNodeRef = *headRef;
	}

	*headRef = sortedHeadRef;
}

void List_print (struct nodeStruct *headRef) {
	struct nodeStruct *currentNodeRef = headRef;

	while (currentNodeRef != NULL) {
		printf("%d ", currentNodeRef -> item);
		currentNodeRef = currentNodeRef -> next;
	}

	printf("\n");
}
