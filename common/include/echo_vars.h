#include <stdio.h>

#define ECHO_INT(var) \
  printf("%s = %d\n", #var, var);

#define ECHO_INT_ARRAY(var, size) \
  printf("%s:\n", #var);          \
  for (int i = 0; i < size; i++)  \
    printf("  [%03d] = %d\n", i, var[i]);

#define ECHO_STRING(var) \
  printf("%s = %s\n", #var, var);
