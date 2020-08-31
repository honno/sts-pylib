#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/cephes.h"
#include "../include/externs.h"
#include "../include/matrix.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                              R A N K  T E S T
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

double Rank(unsigned char epsilon[], int n) {
  int N, i, k, r;
  double p_value, product, chi_squared, arg1, p_32, p_31, p_30, R, F_32, F_31,
      F_30;
  BitSequence **matrix = create_matrix(32, 32), **m;

  N = n / (32 * 32);
  if (isZero(N)) {
    printf("\t\tRANK TEST\n");
    printf("Error: Insuffucient # Of Bits To Define An 32x32 (%dx%d) Matrix\n",
           32, 32);
    p_value = 0.00;
  } else {
    r = 32; /* COMPUTE PROBABILITIES */
    product = 1;
    for (i = 0; i <= r - 1; i++)
      product *= ((1.e0 - pow(2, i - 32)) * (1.e0 - pow(2, i - 32))) /
                 (1.e0 - pow(2, i - r));
    p_32 = pow(2, r * (32 + 32 - r) - 32 * 32) * product;

    r = 31;
    product = 1;
    for (i = 0; i <= r - 1; i++)
      product *= ((1.e0 - pow(2, i - 32)) * (1.e0 - pow(2, i - 32))) /
                 (1.e0 - pow(2, i - r));
    p_31 = pow(2, r * (32 + 32 - r) - 32 * 32) * product;

    p_30 = 1 - (p_32 + p_31);

    F_32 = 0;
    F_31 = 0;
    for (k = 0; k < N; k++) { /* FOR EACH 32x32 MATRIX   */
      matrix = def_matrix(epsilon, 32, 32, matrix, k);
#if (DISPLAY_MATRICES == 1)
      display_matrix(32, 32, matrix);
#endif
      R = computeRank(32, 32, matrix);
      if (R == 32) F_32++; /* DETERMINE FREQUENCIES */
      if (R == 31) F_31++;
    }
    F_30 = (double)N - (F_32 + F_31);

    chi_squared = (pow(F_32 - N * p_32, 2) / (double)(N * p_32) +
                   pow(F_31 - N * p_31, 2) / (double)(N * p_31) +
                   pow(F_30 - N * p_30, 2) / (double)(N * p_30));

    arg1 = -chi_squared / 2.e0;

    printf("\t\tRANK TEST\n");
    printf("---------------------------------------------\n");
    printf("COMPUTATIONAL INFORMATION:\n");
    printf("---------------------------------------------\n");
    printf("(a) Probability P_%d = %f\n", 32, p_32);
    printf("(b)             P_%d = %f\n", 31, p_31);
    printf("(c)             P_%d = %f\n", 30, p_30);
    printf("(d) Frequency   F_%d = %d\n", 32, (int)F_32);
    printf("(e)             F_%d = %d\n", 31, (int)F_31);
    printf("(f)             F_%d = %d\n", 30, (int)F_30);
    printf("(g) # of matrices    = %d\n", N);
    printf("(h) Chi^2            = %f\n", chi_squared);
    printf("(i) NOTE: %d BITS WERE DISCARDED.\n", n % (32 * 32));
    printf("---------------------------------------------\n");

    p_value = exp(arg1);
    if (isNegative(p_value) || isGreaterThanOne(p_value))
      printf("WARNING:  P_VALUE IS OUT OF RANGE.\n");

    for (i = 0; i < 32; i++) /* DEALLOCATE MATRIX  */
      free(matrix[i]);
    free(matrix);
  }
  printf("p_value = %f\n", p_value);

  return p_value;
}
