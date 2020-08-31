#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/cephes.h"
#include "../include/externs.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                    C U M U L A T I V E  S U M S  T E S T
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

double CumulativeSumsForward(unsigned char epsilon[], int n) {
  int S, sup, inf, z, zrev, k;
  double sum1, sum2, p_value;

  S = 0;
  sup = 0;
  inf = 0;
  for (k = 0; k < n; k++) {
    epsilon[k] ? S++ : S--;
    if (S > sup) sup++;
    if (S < inf) inf--;
    z = (sup > -inf) ? sup : -inf;
    zrev = (sup - S > S - inf) ? sup - S : S - inf;
  }

  // forward
  sum1 = 0.0;
  for (k = (-n / z + 1) / 4; k <= (n / z - 1) / 4; k++) {
    sum1 += cephes_normal(((4 * k + 1) * z) / sqrt(n));
    sum1 -= cephes_normal(((4 * k - 1) * z) / sqrt(n));
  }
  sum2 = 0.0;
  for (k = (-n / z - 3) / 4; k <= (n / z - 1) / 4; k++) {
    sum2 += cephes_normal(((4 * k + 3) * z) / sqrt(n));
    sum2 -= cephes_normal(((4 * k + 1) * z) / sqrt(n));
  }

  p_value = 1.0 - sum1 + sum2;

  printf("      CUMULATIVE SUMS (FORWARD) TEST\n");
  printf("-------------------------------------------\n");
  printf("COMPUTATIONAL INFORMATION:\n");
  printf("-------------------------------------------\n");
  printf("(a) The maximum partial sum = %d\n", z);
  printf("-------------------------------------------\n");
  if (isNegative(p_value) || isGreaterThanOne(p_value))
    printf("WARNING:  P_VALUE IS OUT OF RANGE\n");
  printf("p_value = %f\n", p_value);

  return p_value;
}

double CumulativeSumsBackward(unsigned char epsilon[], int n) {
  int S, sup, inf, z, zrev, k;
  double sum1, sum2, p_value;

  S = 0;
  sup = 0;
  inf = 0;
  for (k = 0; k < n; k++) {
    epsilon[k] ? S++ : S--;
    if (S > sup) sup++;
    if (S < inf) inf--;
    z = (sup > -inf) ? sup : -inf;
    zrev = (sup - S > S - inf) ? sup - S : S - inf;
  }

  // backwards
  sum1 = 0.0;
  for (k = (-n / zrev + 1) / 4; k <= (n / zrev - 1) / 4; k++) {
    sum1 += cephes_normal(((4 * k + 1) * zrev) / sqrt(n));
    sum1 -= cephes_normal(((4 * k - 1) * zrev) / sqrt(n));
  }
  sum2 = 0.0;
  for (k = (-n / zrev - 3) / 4; k <= (n / zrev - 1) / 4; k++) {
    sum2 += cephes_normal(((4 * k + 3) * zrev) / sqrt(n));
    sum2 -= cephes_normal(((4 * k + 1) * zrev) / sqrt(n));
  }
  p_value = 1.0 - sum1 + sum2;

  printf("      CUMULATIVE SUMS (REVERSE) TEST\n");
  printf("-------------------------------------------\n");
  printf("COMPUTATIONAL INFORMATION:\n");
  printf("-------------------------------------------\n");
  printf("(a) The maximum partial sum = %d\n", zrev);
  printf("-------------------------------------------\n");
  if (isNegative(p_value) || isGreaterThanOne(p_value))
    printf("WARNING:  P_VALUE IS OUT OF RANGE\n");
  printf("p_value = %f\n", p_value);

  return p_value;
}
