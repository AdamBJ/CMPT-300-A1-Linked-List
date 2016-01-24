// Sample test routine for the list module.
#include <stdio.h>
#include "list.h"
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>


int main(int argc, char** argv)
{
	printf("Starting tests...\n");
	struct nodeStruct *head = NULL;

	// Starting count:
	assert(List_countNodes(head) == 0);

	// Create 1 node:
	struct nodeStruct* firstNode = List_createNode(0);
	List_insertHead(&head, firstNode);
	assert(List_countNodes(head) == 1);
	assert(List_findNode(head, 0) == firstNode);
	assert(List_findNode(head, 1) == NULL);

	// Insert tail:
	struct nodeStruct* lastNode = List_createNode(-5);
	List_insertTail(&head, lastNode);
	assert(List_countNodes(head) == 2);
	assert(List_findNode(head, 0) == firstNode);
	assert(List_findNode(head, -5) == lastNode);
	assert(List_findNode(head, 1) == NULL);

	// Verify list:
	struct nodeStruct *current = head;
	assert(current->item == 0);
	assert(current->next != NULL);
	current = current->next;
	assert(current->item == -5);
	assert(current->next == NULL);

	// Sort and verify:
    List_sort(&head);
    current = head;
    assert(current->item == -5);
    assert(current->next != NULL);
    current = current->next;
    assert(current->item == 0);
    assert(current->next == NULL);

	// Delete
	assert(List_countNodes(head) == 2);
	List_deleteNode(&head, firstNode);
	assert(List_countNodes(head) == 1);
	assert(List_findNode(head, -5) == NULL);
	assert(List_findNode(head, 0) != NULL);
	assert(List_findNode(head, 1) == NULL);
	current = head;
	assert(current->item == 0);
	assert(current->next == NULL);

	// Adam tests
	struct nodeStruct *nonIntTrubbi = List_createNode("fart");

	struct nodeStruct *dupiTroubleMaker = List_createNode(-666);
	List_insertHead(&head, dupiTroubleMaker);
	List_print(head);

	printf("Nodes before: %d\n", List_countNodes(head));
	List_insertHead(&head, dupiTroubleMaker);
	List_insertTail(&head, dupiTroubleMaker);
	printf("Nodes after: %d\n", List_countNodes(head));

	srand(time(NULL));

	for (int i = 0; i < 5; i++) {
		if(i % 2 == 0) {
			List_insertHead(&head, List_createNode(rand()/10000));
			List_insertTail(&head, List_createNode(rand()));
		} else {
			List_insertHead(&head, List_createNode(rand() / -10000));
			List_insertTail(&head, List_createNode(rand() * -1));
		}
	}

	// Insert NULL pointer at head and tail
	struct nodeStruct *theBeast666 = NULL;
	List_insertHead(&head, List_createNode(9));
	printf("Nodes before: %d\n", List_countNodes(head));
	List_insertHead(&head, theBeast666);
	List_insertTail(&head, theBeast666);
	printf("Nodes after: %d\n", List_countNodes(head));
	printf("Before sort:");
	List_print(head);
	printf("\nAfter sort:");
	List_sort(&head);
	List_print(head);

	printf("\nExecution finished.\n");
	return 0;
}
