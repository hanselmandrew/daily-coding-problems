#include <stdio.h>
#include <stdlib.h>

#include "../../common/include/echo_vars.h"

int numberOfPossibleDecodings(char *inputMessage, int inputMessageLength, char *outputMessage, int outputMessageLength);

int main()
{
  /* Read inputs */
  int inputMessageLength;
  char *inputMessage;
  int solutionNumberOfDecodings;

  scanf("%d", &inputMessageLength);
  inputMessage = malloc(sizeof(char) * inputMessageLength);
  scanf("%s", inputMessage);
  scanf("%d", &solutionNumberOfDecodings);

  /* Echo inputs */
  ECHO_INT(inputMessageLength);
  ECHO_STRING(inputMessage);
  ECHO_INT(solutionNumberOfDecodings);

  /* Determine number of possible decodings */
  printf("Possible decodings:\n");
  char * outputMessage = malloc(sizeof(char) * inputMessageLength);
  int totalDecodingCombinations = numberOfPossibleDecodings(inputMessage, inputMessageLength, outputMessage, 0);

  /* Compare solutions */
  printf("%12s -> %12s\n", "Our Solution", "Input Solution");
  printf("%12d -> %12d\n", totalDecodingCombinations, solutionNumberOfDecodings);

  /* Free resources */
  free(inputMessage);
  free(outputMessage);

  return 0;
}

int numberOfPossibleDecodings(char *inputMessage, int inputMessageLength, char *outputMessage, int outputMessageLength)
{
  int totalDecodingCombinations = 0;

  /* If solution to args exists in memoization struct */
  /* return lookup value instead of proceeding */

  if (inputMessageLength == 0)
  {
    printf("  %s\n", outputMessage);
    return 1;
  }
  else if (inputMessageLength > 0)
  {
    if (inputMessage[0] >= '1' && inputMessage[0] <= '9')
    {
      outputMessage[outputMessageLength] = inputMessage[0] + 48;
      totalDecodingCombinations += numberOfPossibleDecodings(&inputMessage[1], inputMessageLength - 1, outputMessage, outputMessageLength + 1);
      outputMessage[outputMessageLength] = '\0';

      if (inputMessageLength > 1)
      {
        if ((inputMessage[0] == '1' && (inputMessage[1] >= '0' && inputMessage[1] <= '9')) ||
            (inputMessage[0] == '2' && (inputMessage[1] >= '0' && inputMessage[1] <= '6')))
        {
          outputMessage[outputMessageLength] =
              96 + ((inputMessage[0] - 48) * 10) +
              (inputMessage[1] - 48);
          totalDecodingCombinations += numberOfPossibleDecodings(&inputMessage[2], inputMessageLength - 2, outputMessage, outputMessageLength + 1);
          outputMessage[outputMessageLength] = '\0';
        }
      }
    }
  }

  return totalDecodingCombinations;
}
