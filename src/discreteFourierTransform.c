#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/cephes.h"
#include "../include/externs.h"
#include "../include/utilities.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
         D I S C R E T E  F O U R I E R  T R A N S F O R M  T E S T
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void __ogg_fdrffti(int n, double *wsave, int *ifac);
void __ogg_fdrfftf(int n, double *X, double *wsave, int *ifac);

double DiscreteFourierTransform(unsigned char epsilon[], int n) {
  double p_value, upperBound, percentile, N_l, N_o, d, *m, *X, *wsave;
  int i, count, ifac[15];

  if (((X = (double *)calloc(n, sizeof(double))) == NULL) ||
      ((wsave = (double *)calloc(2 * n, sizeof(double))) == NULL) ||
      ((m = (double *)calloc(n / 2 + 1, sizeof(double))) == NULL)) {
    printf("\t\tUnable to allocate working arrays for the DFT.\n");
    if (X != NULL) free(X);
    if (wsave != NULL) free(wsave);
    if (m != NULL) free(m);
    return;
  }
  for (i = 0; i < n; i++) X[i] = 2 * (int)epsilon[i] - 1;

  __ogg_fdrffti(n, wsave, ifac);    /* INITIALIZE WORK ARRAYS */
  __ogg_fdrfftf(n, X, wsave, ifac); /* APPLY FORWARD FFT */

  m[0] = sqrt(X[0] * X[0]); /* COMPUTE MAGNITUDE */

  for (i = 0; i < n / 2; i++)
    m[i + 1] = sqrt(pow(X[2 * i + 1], 2) + pow(X[2 * i + 2], 2));
  count = 0; /* CONFIDENCE INTERVAL */
  upperBound = sqrt(2.995732274 * n);
  for (i = 0; i < n / 2; i++)
    if (m[i] < upperBound) count++;
  percentile = (double)count / (n / 2) * 100;
  N_l = (double)count; /* number of peaks less than h = sqrt(3*n) */
  N_o = (double)0.95 * n / 2.0;
  d = (N_l - N_o) / sqrt(n / 4.0 * 0.95 * 0.05);
  p_value = erfc(fabs(d) / sqrt(2.0));

  printf("\t\tFFT TEST\n");
  printf("-------------------------------------------\n");
  printf("COMPUTATIONAL INFORMATION:\n");
  printf("-------------------------------------------\n");
  printf("(a) Percentile = %f\n", percentile);
  printf("(b) N_l        = %f\n", N_l);
  printf("(c) N_o        = %f\n", N_o);
  printf("(d) d          = %f\n", d);
  printf("-------------------------------------------\n");
  printf("p_value = %f\n", p_value);

  free(X);
  free(wsave);
  free(m);

  return p_value;
}
