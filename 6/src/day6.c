#include <stdio.h>
#include <stdlib.h>

#include "../../common/include/echo_vars.h"

typedef struct xorNode_s xorNode_t;
typedef struct xorNode_s
{
  xorNode_t* prev;
  void * xorPointer;
  xorNode_t* next;

  int value;
} xorNode_t;

typedef struct xorList_s
{
  xorNode_t* startNode_ptr;
  xorNode_t* endNode_ptr;
} xorList_t;

/* List functions */
void xorList_free(xorList_t* xorList_ptr);
void xorList_insertStart(xorList_t* xorList_ptr, int value);
void xorList_insertEnd(xorList_t* xorList_ptr, int value);
xorNode_t* xorList_getNodeFromIndex(xorList_t* xorList_ptr, int value);

/* General Functions */
void* xorPointers(void* ptr1, void* ptr2);

int main()
{
  /* Get inputs */
  int numberOfNodes;
  int* nodeValues;
  int* insertEnd;

  scanf("%d", &numberOfNodes);
  nodeValues = malloc(sizeof(int) * numberOfNodes);
  insertEnd = malloc(sizeof(int) * numberOfNodes);

  for(int i = 0; i < numberOfNodes; i++)
  {
    scanf("%d", &nodeValues[i]);
  }
  for(int i = 0; i < numberOfNodes; i++)
  {
    scanf("%d", &insertEnd[i]);
  }

  /* Echo inputs for clarity */
  ECHO_INT(numberOfNodes);
  ECHO_INT_ARRAY(nodeValues, numberOfNodes);
  ECHO_INT_ARRAY(insertEnd, numberOfNodes)

  /* Create doubly linked list from inputs */
  xorList_t xorList;
  xorList.startNode_ptr = NULL;
  xorList.endNode_ptr = NULL;

  for(int i = 0; i < numberOfNodes; i++)
  {
    if(insertEnd[i] == 1)
      xorList_insertEnd(&xorList, nodeValues[i]);
    else if (insertEnd[i] == 0)
      xorList_insertStart(&xorList, nodeValues[i]);
  }

  /* Traverse linked list and check that values match original input */
  xorNode_t* currentNode_ptr = xorList.startNode_ptr;
  xorNode_t* prevNode_ptr = NULL;
  
  printf("Forward List:\n");
  for(int i = 0; i < numberOfNodes; i++)
  {
    printf("  [%03d] -> (%d)\n", i, currentNode_ptr->value);
    xorNode_t* temp = currentNode_ptr;
    currentNode_ptr = xorPointers(currentNode_ptr->xorPointer, prevNode_ptr);
    prevNode_ptr = temp;
  }

  currentNode_ptr = xorList.endNode_ptr;
  prevNode_ptr = NULL;
  printf("Backward List:\n");
  for(int i = 0; i < numberOfNodes; i++)
  {
    printf("  [%03d] -> (%d)\n", (numberOfNodes-1)-i, currentNode_ptr->value);
    xorNode_t* temp = currentNode_ptr;
    currentNode_ptr = xorPointers(currentNode_ptr->xorPointer, prevNode_ptr);
    prevNode_ptr = temp;
  }

  return 0;
}

void xorList_insertStart(xorList_t* xorList_ptr, int value)
{
  xorNode_t* newNode_ptr = malloc(sizeof(xorNode_t));
  newNode_ptr->prev = NULL; 
  newNode_ptr->next = xorList_ptr->startNode_ptr; 

  newNode_ptr->xorPointer = xorPointers(NULL, xorList_ptr->startNode_ptr);
  newNode_ptr->value = value;

  if (xorList_ptr->startNode_ptr == NULL)
  {
    xorList_ptr->startNode_ptr = newNode_ptr;
    xorList_ptr->endNode_ptr = newNode_ptr;
  }
  else
  {
    xorNode_t* prevStartNode_ptr = xorList_ptr->startNode_ptr;
    prevStartNode_ptr->xorPointer = 
      xorPointers(
        newNode_ptr, 
        xorPointers(prevStartNode_ptr->xorPointer, NULL)
      );
    prevStartNode_ptr->next = newNode_ptr;

    xorList_ptr->startNode_ptr = newNode_ptr;
  }
}

void xorList_insertEnd(xorList_t* xorList_ptr, int value)
{
  xorNode_t* newNode_ptr = malloc(sizeof(xorNode_t));
  newNode_ptr->prev = xorList_ptr->endNode_ptr; 
  newNode_ptr->next = NULL; 

  newNode_ptr->xorPointer = xorPointers(xorList_ptr->endNode_ptr, NULL);
  newNode_ptr->value = value;

  if (xorList_ptr->endNode_ptr == NULL)
  {
    xorList_ptr->startNode_ptr = newNode_ptr;
    xorList_ptr->endNode_ptr = newNode_ptr;
  }
  else
  {
    xorNode_t* prevEndNode_ptr = xorList_ptr->endNode_ptr;
    prevEndNode_ptr->xorPointer =
      xorPointers(
        xorPointers(prevEndNode_ptr->xorPointer, NULL),
        newNode_ptr
      );
    prevEndNode_ptr->next = newNode_ptr;
    
    xorList_ptr->endNode_ptr = newNode_ptr;
  }
}

void* xorPointers(void* ptr1, void* ptr2)
{
  void* xorPtr;

  xorPtr =
    (void*) (
      ((__PTRDIFF_TYPE__) ptr1) ^ 
      ((__PTRDIFF_TYPE__) ptr2)
    );

  return xorPtr;
}
