#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define ECHO_INT(var) \
  printf("%s = %d\n", #var, var)

bool doesAnyPairSumEqualK(int *valueArray, int arraySize, int k);
int compare_ints(const void *p, const void *q);

int main()
{
  int k;
  int arraySize;
  int *valueArray;

  /* Get inputs from stdin */
  scanf("%d", &k);
  scanf("%d", &arraySize);
  valueArray = malloc(arraySize * sizeof(int));
  for (int i = 0; i < arraySize; i++)
  {
    scanf("%d", &valueArray[i]);
  }

  /* Echo inputs */
  ECHO_INT(k);
  ECHO_INT(arraySize);
  for (int i = 0; i < arraySize; i++)
  {
    ECHO_INT(i);
    ECHO_INT(valueArray[i]);
  }

  /* Operate on inputs */
  doesAnyPairSumEqualK(valueArray, arraySize, k);

  /* Free memory for valueArray */
  free(valueArray);
}

bool doesAnyPairSumEqualK(int *valueArray, int arraySize, int k)
{
  qsort(valueArray, arraySize, sizeof(*valueArray), compare_ints);
  
  for (int i = 0; i < arraySize; i++)
  {
    ECHO_INT(i);
    ECHO_INT(valueArray[i]);
  }
  
  return false;
}

int compare_ints(const void *p, const void *q)
{
    int x = *(const int *)p;
    int y = *(const int *)q;

    if (x < y)
        return -1;
    else if (x > y)
        return 1;
    return 0;
}
