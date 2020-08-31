#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../include/erf.h"
#include "../include/externs.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                          F R E Q U E N C Y  T E S T
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

double Frequency(unsigned char epsilon[], int n) {
  int i;
  double f, s_obs, p_value, sum, sqrt2 = 1.41421356237309504880;

  sum = 0.0;
  for (i = 0; i < n; i++) sum += 2 * (int)epsilon[i] - 1;
  s_obs = fabs(sum) / sqrt(n);
  f = s_obs / sqrt2;
  p_value = erfc(f);

  printf("\t      FREQUENCY TEST\n");
  printf("---------------------------------------------\n");
  printf("COMPUTATIONAL INFORMATION:\n");
  printf("(a) The nth partial sum = %d\n", (int)sum);
  printf("(b) S_n/n               = %f\n", sum / n);
  printf("---------------------------------------------\n");
  printf("p_value = %f\n", p_value);

  return p_value;
}
