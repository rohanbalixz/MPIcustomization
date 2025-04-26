#include <stdio.h>
#include "secret_function.h"

int main() {
  double v = secret_function(100.0, 100.0);
  printf("secret_function(100.0,100.0) = %lf\n", v);
  return 0;
}

