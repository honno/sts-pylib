#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../include/cephes.h"
#include "../include/externs.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                    B L O C K  F R E Q U E N C Y  T E S T
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

double BlockFrequency(unsigned char epsilon[], int M, int n) {
  int i, j, N, blockSum;
  double p_value, sum, pi, v, chi_squared;

  N = n / M; /* # OF SUBSTRING BLOCKS      */
  sum = 0.0;

  for (i = 0; i < N; i++) {
    blockSum = 0;
    for (j = 0; j < M; j++) blockSum += epsilon[j + i * M];
    pi = (double)blockSum / (double)M;
    v = pi - 0.5;
    sum += v * v;
  }
  chi_squared = 4.0 * M * sum;
  p_value = cephes_igamc(N / 2.0, chi_squared / 2.0);

  printf("\tBLOCK FREQUENCY TEST\n");
  printf("---------------------------------------------\n");
  printf("COMPUTATIONAL INFORMATION:\n");
  printf("---------------------------------------------\n");
  printf("(a) Chi^2           = %f\n", chi_squared);
  printf("(b) # of substrings = %d\n", N);
  printf("(c) block length    = %d\n", M);
  printf("(d) Note: %d bits were discarded.\n", n % M);
  printf("---------------------------------------------\n");
  printf("p_value = %f\n", p_value);

  return p_value;
}
