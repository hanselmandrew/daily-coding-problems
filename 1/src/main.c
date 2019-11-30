#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define ECHO_INT(var) \
  printf("%s = %d\n", #var, var)

bool doesAnyPairSumEqualK(int *valueArray, int arraySize, int k, int *lowVal, int *val2);
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
  int val1, val2;
  bool pairExists =
      doesAnyPairSumEqualK(valueArray, arraySize, k, &val1, &val2);
  if (pairExists)
  {
    printf("Match found with values %d and %d\n", val1, val2);
  }
  else
  {
    printf("No match found\n");
  }
  

  /* Free memory for valueArray */
  free(valueArray);
}

bool doesAnyPairSumEqualK(int *valueArray, int arraySize, int k, int *lowVal, int *highVal)
{
  qsort(valueArray, arraySize, sizeof(*valueArray), compare_ints);

  int lowValIndex = 0;
  int highValIndex = arraySize - 1;

  while (lowValIndex != highValIndex)
  {
    int sum = valueArray[lowValIndex] + valueArray[highValIndex];
    if (sum == k)
    {
      *lowVal = valueArray[lowValIndex];
      *highVal = valueArray[highValIndex];
      return true;
    }
    else if (sum > k)
    {
      highValIndex--;
    }
    else if (sum < k)
    {
      lowValIndex++; 
    }
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
