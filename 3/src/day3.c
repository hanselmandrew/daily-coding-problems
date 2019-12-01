#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../../common/include/echo_vars.h"

/* Structures */
typedef struct binaryTreeNode_s binaryTreeNode_t;
typedef struct binaryTreeNode_s
{
  int val;
  binaryTreeNode_t *left;
  binaryTreeNode_t *right;
} binaryTreeNode_t;

typedef struct treeDeserializationInfo_s
{
  int parseIndex;

  char *inputString;
  int inputStringLength;

  int nodeCount;
  int maxDepth;
} treeDeserializationInfo_t;

/* Prototypes */
int serializeBinaryTree(binaryTreeNode_t *root, char *outputString);
int deserializeBinaryTree(char *inputString, int inputStringLength, binaryTreeNode_t **rootPtr);
int deserializeBinaryNode(treeDeserializationInfo_t *info, binaryTreeNode_t **nodePtr);
int parseNodePointer(treeDeserializationInfo_t *info, binaryTreeNode_t **nodePtr);

int main()
{
  /* Get inputs from stdin */
  char inputString[] = "(1,  (2,  0,  0),\n (3, 0, 0))";

  /* Echo inputs */
  ECHO_STRING(inputString);

  /* Operate on inputs */
  /* Deserialize string */
  /* In-order traversal */
  /* Serialize */
  binaryTreeNode_t * treeRoot;
  deserializeBinaryTree(inputString, strlen(inputString), &treeRoot);

  /* Validate solution */
  ECHO_STRING(inputString);

  /* In-order traversal values */
  /* Serialized value compare */

  return 0;
}

int serializeBinaryTree(binaryTreeNode_t *root, char *outputString)
{
  return -1;
}

/* Parses tree input string and modifies root to point to root of tree */
int deserializeBinaryTree(char *inputString, int inputStringLength, binaryTreeNode_t **rootPtr)
{
  int errorCode = 0;
  treeDeserializationInfo_t info =
      {
          .parseIndex = 0,
          .inputString = inputString,
          .inputStringLength = inputStringLength,
          .nodeCount = 0,
          .maxDepth = 0};

  if (NULL == inputString)
  {
    errorCode = -1;
  }

  /* sanitizeInputString() */ /* remove whitespace, check parentheses count */
  {
    int replaceIndex = 0;
    int hangingParentheses = 0;

    for (int stringIndex = 0; stringIndex < info.inputStringLength; stringIndex++)
    {
      char currentChar = info.inputString[stringIndex];

      /* remove whitespace by ingoring those chars when copying in place*/
      if (!isspace(currentChar))
      {
        info.inputString[replaceIndex] = currentChar;
        replaceIndex++;

        /* Count parentheses */
        if ('(' == currentChar)
        {
          hangingParentheses++;
        }
        else if (')' == currentChar)
        {
          hangingParentheses--;
        }
      }
    }

    info.inputString[replaceIndex] = '\0';
    info.inputStringLength = replaceIndex + 1;

    if (hangingParentheses != 0)
    {
      return -1;
    }
  }

  /* Init root state */
  char rootChar;
  if (sscanf(&inputString[info.parseIndex], "%c", &rootChar))
  {
    info.parseIndex++;
  }
  if (rootChar == '(')
  {
    /* allocate memory for a new node and recurse on new node */
    {
      *rootPtr = malloc(sizeof(binaryTreeNode_t));
      if (*rootPtr == NULL)
      {
        return -1;
      }
      else
      {
        /* initNode(root) */ {
          (*rootPtr)->val = 0;
          (*rootPtr)->left = NULL;
          (*rootPtr)->right = NULL;
        }
        int returnVal = deserializeBinaryNode(&info, rootPtr);
        if (returnVal)
        {
          errorCode = -1;
        }
      }
    }
  }
  else
  {
    errorCode = -1;
  }

  if (errorCode)
  {
    /* TODO: Free allocated tree memory */
    /* free left */
    /* free right */
    /* don't free root, it was allocated and may be used by caller */
    return errorCode;
  }
  else
  {
    return 0;
  }
}

int deserializeBinaryNode(treeDeserializationInfo_t *info, binaryTreeNode_t **nodePtr)
{
  /* root val */
  /* parseNodeVal(info, root->val) */ {
    /* try to get a int value, only option */
    int nodeVal;
    char tempBuffer[12];
    int sscanfReturnVal = 0;

    sscanfReturnVal = sscanf(&(info->inputString[info->parseIndex]), "%d", &nodeVal);
    if (!sscanfReturnVal || sscanfReturnVal == EOF)
      return -1;
    (*nodePtr)->val = nodeVal;

    /* Advance parseIndex */
    snprintf(tempBuffer, 12, "%d", nodeVal);
    info->parseIndex += strlen(tempBuffer);
  }

  /* Skip comma */
  info->parseIndex++;

  /* left */
  if (parseNodePointer(info, &((*nodePtr)->left)))
  {
    return -1;
  }

  /* Skip comma */
  info->parseIndex++;

  /* right */
  if (parseNodePointer(info, &((*nodePtr)->right)))
  {
    return -1;
  }

  /* Check for ) */
  {
    char nodeChar;
    int sscanfReturnVal = 0;

    sscanfReturnVal = sscanf(&(info->inputString[info->parseIndex]), "%c", &nodeChar);
    if (!sscanfReturnVal || sscanfReturnVal == EOF)
      return -1;

    if (nodeChar != ')')
      return -1;

    /* Advance parseIndex */
    info->parseIndex++;
  }

  /* Everything is good! */
  return 0;
}

int parseNodePointer(treeDeserializationInfo_t *info, binaryTreeNode_t **nodePtr)
{
  /* try to get int value */
  int nodeVal;
  char nodeChar;
  int sscanfReturnVal;
  char tempBuffer[12];

  sscanfReturnVal = sscanf(&(info->inputString[info->parseIndex]), "%d", &nodeVal);
  if (sscanfReturnVal != EOF)
  {
    if (sscanfReturnVal)
    {
      if (nodeVal == 0)
      {
        (*nodePtr) = NULL;
      }
      else
      {
        return -1; /* there shouldn't be any non-zero values in left/right fields */
      }

      /* Advance parseIndex */
      snprintf(tempBuffer, 12, "%d", nodeVal);
      info->parseIndex += strlen(tempBuffer);
    }
    else
    {
      sscanfReturnVal = sscanf(&(info->inputString[info->parseIndex]), "%c", &nodeChar);
      if (!sscanfReturnVal || nodeChar != '(' || sscanfReturnVal == EOF)
      {
        return -1; /* something other than ( encountered or other error */
      }
      else
      {
        /* Advance parseIndex */
        info->parseIndex++;

        /* allocate memory for a new node and recurse on new node */
        (*nodePtr) = malloc(sizeof(binaryTreeNode_t));
        if ((*nodePtr) == NULL)
        {
          return -1; /* bad malloc */
        }
        else
        {
          /* initNode(nodePtr)) */ {
            (*nodePtr)->val = 0;
            (*nodePtr)->left = NULL;
            (*nodePtr)->right = NULL;
          }
          int returnVal = deserializeBinaryNode(info, nodePtr);
          if (returnVal)
          {
            return -1; /* propogate error */
          }
        }
      }
    }
  }
  else
  {
    return -1; /* wasn't valid null or new node */
  }

  return 0;
}