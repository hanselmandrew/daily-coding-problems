#include <stdio.h>
#include <stdlib.h>

#define ECHO_INT(var) \
  printf("%s = %d\n", #var, var);

#define ECHO_INT_ARRAY(var, size) \
  for (int i = 0; i < size; i++)  \
    printf("%s[%d] = %d\n", #var, i, var[i]);

void calculateProductOfOthers(int *originalValues, int *productOfOthers, int arraySize);

int main()
{
  int arraySize = 0;
  int *valueArray = NULL;
  int *productArray = NULL;
  int *solutionArray = NULL;

  /* Get inputs from stdin */
  scanf("%d", &arraySize);
  valueArray = malloc(arraySize * sizeof(int));
  productArray = malloc(arraySize * sizeof(int));
  for (int i = 0; i < arraySize; i++)
  {
    scanf("%d", &valueArray[i]);
  }

  solutionArray = malloc(arraySize * sizeof(int));
  for (int i = 0; i < arraySize; i++)
  {
    scanf("%d", &solutionArray[i]);
  }

  /* Echo inputs */
  ECHO_INT(arraySize);
  ECHO_INT_ARRAY(valueArray, arraySize);
  ECHO_INT_ARRAY(solutionArray, arraySize);

  /* Operate on inputs */
  calculateProductOfOthers(valueArray, productArray, arraySize);

  /* Check out solution against given solution */
  printf("%15s -> %15s\n", "our solution", "input solution");
  for (int i = 0; i < arraySize; i++)
  {
    printf("%15d -> %15d\n", productArray[i], solutionArray[i]);
  }

  return 0;
}

void calculateProductOfOthers(int *originalValues, int *productOfOthers, int arraySize)
{
  int *leftProduct = malloc(sizeof(int) * arraySize);
  int *rightProduct = malloc(sizeof(int) * arraySize);

  /* Copy original into product array */
  /* Could potentially replace with memcpy */
  for (int i = 0; i < arraySize; i++)
  {
    leftProduct[i] = originalValues[i];
    rightProduct[i] = originalValues[i];
  }

  /* Calculate cumulative product from beginning/end to current index */
  for (int i = 1; i < arraySize; i++)
  {
    leftProduct[i] = leftProduct[i] * leftProduct[i - 1];
    rightProduct[(arraySize - 1) - i] = rightProduct[(arraySize - 1) - i] * rightProduct[(arraySize - 1) - (i - 1)];
  }

  /* Value at index is equal to product of cummulative left sum i-1 and cummulative right sum of i+1 */
  for (int i = 0; i < arraySize; i++)
  {
    int leftProductVal, rightProductVal;
    if (i == 0)
    {
      leftProductVal = 1;
    }
    else
    {
      leftProductVal = leftProduct[i - 1];
    }

    if (i == arraySize - 1)
    {
      rightProductVal = 1;
    }
    else
    {
      rightProductVal = rightProduct[i + 1];
    }

    productOfOthers[i] = leftProductVal * rightProductVal;
  }

  free(leftProduct);
  free(rightProduct);
}
