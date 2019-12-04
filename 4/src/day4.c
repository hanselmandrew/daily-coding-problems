#include <stdio.h>
#include <stdlib.h>
#include "../../common/include/echo_vars.h"

int findFirstMissingPositiveInt(int *arrayValues, int arrayLength);

int main()
{
  /* Program vars */
  int arrayLength;
  int *arrayValues;
  int missingValSolution;

  /* Get inputs */
  scanf("%d", &arrayLength);
  arrayValues = malloc(sizeof(int) * arrayLength);
  for (int i = 0; i < arrayLength; i++)
  {
    scanf("%d", &arrayValues[i]);
  }
  scanf("%d", &missingValSolution);

  /* Echo inputs */
  ECHO_INT(arrayLength);
  ECHO_INT_ARRAY(arrayValues, arrayLength);
  ECHO_INT(missingValSolution);

  /* Operate on input */
  int missingVal;
  missingVal = findFirstMissingPositiveInt(arrayValues, arrayLength);

  /* Evaluate solution */
  printf("\n");
  printf("%12s -> %12s\n", "Our Solution", "Input Solution");
  printf("%12d -> %12d\n", missingVal, missingValSolution);

  return 0;
}

int findFirstMissingPositiveInt(int *arrayValues, int arrayLength)
{
  /* Split array, move non-positive integers to the beginning */
  int insertIndex = 0;
  for (int i = 0; i < arrayLength; i++)
  {
    if (arrayValues[i] <= 0)
    {
      if (i > insertIndex)
      {
        int temp = arrayValues[insertIndex];
        arrayValues[insertIndex] = arrayValues[i];
        arrayValues[i] = temp;
      }
      while ((arrayValues[insertIndex] <= 0) && (insertIndex < arrayLength))
      {
        insertIndex++;
      }
    }
  }
  printf("\nSeperate positive from non-positive values\n");
  ECHO_INT_ARRAY(arrayValues, arrayLength);

  /* Recast value to different name for better understanding */
  int positiveStartIndex = insertIndex;

  /* Mark positive elements as existing in place */
  for (int i = positiveStartIndex; i < arrayLength; i++)
  {
    int markIndex = abs(arrayValues[i]) - 1 + positiveStartIndex;
    if (markIndex < arrayLength)
    {
      arrayValues[markIndex] = -abs(arrayValues[markIndex]);
    }
  }
  printf("\nMark elements that are referenced by others\n");
  ECHO_INT_ARRAY(arrayValues, arrayLength);

  /* Find first positive element and return its index */
  for (int i = positiveStartIndex; i <= arrayLength; i++)
  {
    if (arrayValues[i] > 0)
    {
      return (i - positiveStartIndex) + 1;
    }
  }

  /* All positive elements (1-n) exists, return n+1 */
  return arrayLength - positiveStartIndex + 1;
}