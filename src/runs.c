#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/cephes.h"
#include "../include/externs.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                              R U N S  T E S T
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

double Runs(unsigned char epsilon[], int n) {
  int S, k;
  double pi, V, erfc_arg, p_value;

  S = 0;
  for (k = 0; k < n; k++)
    if (epsilon[k]) S++;
  pi = (double)S / (double)n;

  if (fabs(pi - 0.5) > (2.0 / sqrt(n))) {
    printf("\t\tRUNS TEST\n");
    printf("------------------------------------------\n");
    printf("PI ESTIMATOR CRITERIA NOT MET! PI = %f\n", pi);
    p_value = 0.0;
  } else {
    V = 1;
    for (k = 1; k < n; k++)
      if (epsilon[k] != epsilon[k - 1]) V++;

    erfc_arg =
        fabs(V - 2.0 * n * pi * (1 - pi)) / (2.0 * pi * (1 - pi) * sqrt(2 * n));
    p_value = erfc(erfc_arg);

    printf("\t\tRUNS TEST\n");
    printf("------------------------------------------\n");
    printf("COMPUTATIONAL INFORMATION:\n");
    printf("------------------------------------------\n");
    printf("(a) Pi                        = %f\n", pi);
    printf("(b) V_n_obs (Total # of runs) = %d\n", (int)V);
    printf("(c) V_n_obs - 2 n pi (1-pi)\n");
    printf("    -----------------------   = %f\n", erfc_arg);
    printf("      2 sqrt(2n) pi (1-pi)\n");
    printf("------------------------------------------\n");
    if (isNegative(p_value) || isGreaterThanOne(p_value))
      printf("WARNING:  P_VALUE IS OUT OF RANGE.\n");
    printf("p_value = %f\n", p_value);
  }

  return p_value;
}
