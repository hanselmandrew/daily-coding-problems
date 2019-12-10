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

  /* Base recursive case of message length zero prints the resultant decoded message */
  if (inputMessageLength == 0)
  {
    printf("  %s\n", outputMessage);
    return 1;
  }
  else if (inputMessageLength > 0)
  {
    /* Consider decodings where one digit is used for this character */
    if (inputMessage[0] >= '1' && inputMessage[0] <= '9')
    {
      /* Add character to string, recurse, remove character from string */
      outputMessage[outputMessageLength] = inputMessage[0] + 48;
      totalDecodingCombinations += numberOfPossibleDecodings(&inputMessage[1], inputMessageLength - 1, outputMessage, outputMessageLength + 1);
      outputMessage[outputMessageLength] = '\0';

      /* Consider decodings where two digits are used for this character */
      if (inputMessageLength > 1)
      {
        /* Values from 10-26 are valid here */
        if ((inputMessage[0] == '1' && (inputMessage[1] >= '0' && inputMessage[1] <= '9')) ||
            (inputMessage[0] == '2' && (inputMessage[1] >= '0' && inputMessage[1] <= '6')))
        {
          /* Add character to string, recurse, remove character from string */
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
