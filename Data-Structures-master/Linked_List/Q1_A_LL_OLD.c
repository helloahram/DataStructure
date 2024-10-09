//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;				// 데이터 저장하는 공간
	struct _listnode *next; // 다음 노드를 가리키는 포인터
} ListNode;					// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList; // You should not change the definition of LinkedList

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;

	// Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int insertSortedLL(LinkedList *ll, int item)
{
	// 1. newNode 만들고 메모리 할당하기
	// 2-1. Head 가 없거나 Head 보다 작으면 new 를 Head 로 만들기
	// 2-2. 중간이나 끝에 추가할 때는 current node 만들어서 비교하기
	// cur 로 new 가 들어갈 자리를 찾고, cur->next 가 NULL 이 아니거나
	// next->item 이 더 작을 경우 new->next 를 cur->next 로 대체
	// new-next 에 cur->next 를 넣어주고, cur->next 에 new 넣어주기

	// newNode 만들고 메모리 할당해주기
	ListNode *newNode = malloc(sizeof(ListNode));
	if (newNode == NULL) // 메모리 할당 실패인 경우
		return -1;
	newNode->item = item;
	newNode->next = NULL;

	// head 가 없거나 new item 이 head 보다 작으면 head 로 만들어주기
	// new->next 를 ll->head와 이어주고, new 를 head 로 만들기
	if (ll->head == NULL || ll->head->item >= item)
	{
		// 기존 head 를 newNode 의 next 로 보내고
		// newNode 를 head 로 만들기
		newNode->next = ll->head;
		ll->head = newNode;

		ll->size++; // ll size 늘려주기
		return 0;	// index 0 반환
	}
	// current 를 만들고, head 부터 순회 시작
	ListNode *cur = ll->head;
	// index 선언, newNode 가 첫번째가 아니므로 index 1부터 시작
	int index = 1;

	// 현재 노드의 next 가 NULL 이 아니고 현재 노드의 item 이 더 크면
	// 다음 노드로 이동하고 index +1 해주기
	while (cur->next != NULL && cur->next->item < item)
	{
		cur = cur->next; // 다음 노드로 이동
		index++;		 // 다음 노드로 이동 시 index +1
	}
	// 현재 노드의 위치를 찾으면, newNode 에 넣어준다
	newNode->next = cur->next;
	cur->next = newNode;

	ll->size++;

	return index; // index 반환
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll)
{

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL)
	{
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}

ListNode *findNode(LinkedList *ll, int index)
{

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0)
	{
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value)
{

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0)
	{
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}

	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL)
	{
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}

int removeNode(LinkedList *ll, int index)
{

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0)
	{
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL)
	{

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
