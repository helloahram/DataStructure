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
    int item;               // 데이터 저장하는 공간
    struct _listnode *next; // 다음 노드를 가리키는 포인터
} ListNode;                 // You should not change the definition of ListNode

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
    // 1. temp 만들고 ll->head 값 넣어주기
    // 2. head 가 NULL 이거나 head 보다 작으면 temp Insert
    // 3. next 가 NULL 이 아니고 next 보다 크면 index++
    // 4. next 가 NULL 이 아니고 next 보다 작으면 Insert

    // tmp 에 ll->head 값을 대입하여 리스트 탐색 준비
    ListNode *temp = ll->head;
    int index = 0;

    // 리스트가 비었거나, head 보다 작을 때 head 로 설정
    if (temp == NULL || temp->item > item)
    {
        insertNode(ll, index, item); // Node Insert
        return index;                // index 0 return
    }

    // head 와 중복되는 경우 return -1
    if (temp->item == item)
        return -1;

    // next 가 존재하고, next item 이 item 보다 작을 때까지 탐색
    if (temp->next != NULL && temp->next->item < item)
    {
        index++;
        temp = temp->next;
    }

    // next 가 존재하고 next item 과 item 이 중복인 경우 return -1
    if (temp->next != NULL && temp->next->item == item)
        return -1;

    // 중복되지 않은 위치에 Node Insert
    insertNode(ll, index, item);
    return index;
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
        tmp = cur->next; // 다음 노드의 위치를 저장
        free(cur);       // 현재 노드를 해제
        cur = tmp;       // 다음 노드로 이동
    } // cur 을 free() 한 이후에 그 노드에 다시 접근하지 않기 때문에 올바르게 동작한다
    ll->head = NULL;
    ll->size = 0;
}

// findNode 에서 ListNode * (구조체의 포인터) 인 이유는
// 노드의 실제 주소를 반환하고 연결 리스트의 구조를 수정해야 하기 때문
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
