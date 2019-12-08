#include <stdio.h>
#include <stdlib.h>

#include "../../common/include/echo_vars.h"

int main()
{
  /* Read inputs */
  int inputMessageLength;
  char* inputMessage;
  int solutionNumberOfDecodings;

  scanf("%d", &inputMessageLength);
  inputMessage = malloc(sizeof(char) * inputMessageLength);
  scanf("%s", inputMessage);

  /* Echo inputs */
  ECHO_INT(inputMessageLength);
  ECHO_STRING(inputMessage);

  /* Determine number of possible decodings */

  return 0;
}