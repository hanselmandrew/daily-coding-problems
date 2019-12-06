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
void xorList_insertStart(xorList_t* xorList_ptr, int value);
void xorList_insertEnd(xorList_t* xorList_ptr, int value);
void xorList_insertEitherEnd(xorList_t* xorList_ptr, int insertAtStart, int value);
xorNode_t* xorList_getNodeFromIndex(xorList_t* xorList_ptr, int value);
void xorList_free(xorList_t* xorList_ptr);

/* General Functions */
void* xorPointers(void* ptr1, void* ptr2);

int main()
{
  /* Get inputs */
  int numberOfNodes;
  int* nodeValues;
  int* insertEnd;
  int* solutionValues;

  scanf("%d", &numberOfNodes);
  nodeValues = malloc(sizeof(int) * numberOfNodes);
  insertEnd = malloc(sizeof(int) * numberOfNodes);
  solutionValues = malloc(sizeof(int) * numberOfNodes);

  for(int i = 0; i < numberOfNodes; i++)
  {
    scanf("%d", &nodeValues[i]);
  }
  for(int i = 0; i < numberOfNodes; i++)
  {
    scanf("%d", &insertEnd[i]);
  }
  for(int i = 0; i < numberOfNodes; i++)
  {
    scanf("%d", &solutionValues[i]);
  }

  /* Echo inputs for clarity */
  ECHO_INT(numberOfNodes);
  ECHO_INT_ARRAY(nodeValues, numberOfNodes);
  ECHO_INT_ARRAY(insertEnd, numberOfNodes);
  ECHO_INT_ARRAY(solutionValues, numberOfNodes);

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
  printf("  Index   %12s -> %12s\n", "Our Solution", "Input Solution");
  for(int i = 0; i < numberOfNodes; i++)
  {
    printf("  [%03d]  %12d -> %12d\n", i, currentNode_ptr->value, solutionValues[i]);

    xorNode_t* temp = currentNode_ptr;
    currentNode_ptr = xorPointers(currentNode_ptr->xorPointer, prevNode_ptr);
    prevNode_ptr = temp;
  }

  #if 0 /* Traverse the list backwards */
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
  #endif

  xorList_free(&xorList);

  free(nodeValues);
  free(insertEnd);
  free(solutionValues);

  return 0;
}

void xorList_insertEitherEnd(xorList_t* xorList_ptr, int insertAtStart, int value)
{
  xorNode_t* endNode_ptr;
  xorNode_t** xorList_startOrEnd_ptrRef;
  if (insertAtStart)
  {
    endNode_ptr = xorList_ptr->startNode_ptr;
    xorList_startOrEnd_ptrRef = &xorList_ptr->startNode_ptr;
  }
  else
  {
    endNode_ptr = xorList_ptr->endNode_ptr;
    xorList_startOrEnd_ptrRef = &xorList_ptr->endNode_ptr;
  }

  xorNode_t* newNode_ptr = malloc(sizeof(xorNode_t));
  newNode_ptr->xorPointer = xorPointers(NULL, endNode_ptr);
  newNode_ptr->value = value;

  /* If the end node is NULL, this must be the first element in the list,
      just stick the new node in there */
  if (endNode_ptr == NULL)
  {
    xorList_ptr->startNode_ptr = newNode_ptr;
    xorList_ptr->endNode_ptr = newNode_ptr;
  }

  /* Otherwise, place the newNode at the selected end, 
      update the previous endNode's next Xor Pointer 
      (with newNode and previous endNode's previousNode) */
  else
  {
    xorNode_t* prevStartNode_ptr = endNode_ptr;
    prevStartNode_ptr->xorPointer = 
      xorPointers(
        newNode_ptr, 
        xorPointers(prevStartNode_ptr->xorPointer, NULL)
      );
    prevStartNode_ptr->next = newNode_ptr;

    *xorList_startOrEnd_ptrRef = newNode_ptr;
  }
}

void xorList_insertStart(xorList_t* xorList_ptr, int value)
{
  xorList_insertEitherEnd(xorList_ptr, 1, value);
}

void xorList_insertEnd(xorList_t* xorList_ptr, int value)
{
  xorList_insertEitherEnd(xorList_ptr, 0, value);
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

void xorList_free(xorList_t* xorList_ptr)
{
  xorNode_t* currentNode_ptr;
  xorNode_t* prevNode_ptr;
  
  if(xorList_ptr == NULL)
  {
    return;
  }

  currentNode_ptr = xorList_ptr->startNode_ptr;
  if(currentNode_ptr != NULL)
  {
    xorNode_t* nextXorNode;
    xorNode_t* temp = currentNode_ptr;
    currentNode_ptr = xorPointers(currentNode_ptr->xorPointer, prevNode_ptr);
    prevNode_ptr = temp;

    free(prevNode_ptr);
  }
}
