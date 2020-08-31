#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/cephes.h"
#include "../include/externs.h"
#include "../include/utilities.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
               O V E R L A P P I N G  T E M P L A T E  T E S T
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
double Pr(int u, double eta);

double OverlappingTemplateMatchings(unsigned char epsilon[], int m, int n) {
  int i, k, match;
  double W_obs, eta, sum, chi2, p_value, lambda;
  int M, N, j, K = 5;
  unsigned int nu[6] = {0, 0, 0, 0, 0, 0};
  double pi[6] = {0.143783, 0.139430, 0.137319, 0.124314, 0.106209, 0.348945};
  BitSequence *sequence;

  M = 1032;
  N = n / M;

  if ((sequence = (BitSequence *)calloc(m, sizeof(BitSequence))) == NULL) {
    printf("    OVERLAPPING TEMPLATE OF ALL ONES TEST\n");
    printf("---------------------------------------------\n");
    printf(
        "TEMPLATE DEFINITION:  Insufficient memory, Overlapping Template "
        "Matchings test aborted!\n");
  } else
    for (i = 0; i < m; i++) sequence[i] = 1;

  lambda = (double)(M - m + 1) / pow(2, m);
  eta = lambda / 2.0;
  sum = 0.0;
  for (i = 0; i < K; i++) { /* Compute Probabilities */
    pi[i] = Pr(i, eta);
    sum += pi[i];
  }
  pi[K] = 1 - sum;

  for (i = 0; i < N; i++) {
    W_obs = 0;
    for (j = 0; j < M - m + 1; j++) {
      match = 1;
      for (k = 0; k < m; k++) {
        if (sequence[k] != epsilon[i * M + j + k]) match = 0;
      }
      if (match == 1) W_obs++;
    }
    if (W_obs <= 4)
      nu[(int)W_obs]++;
    else
      nu[K]++;
  }
  sum = 0;
  chi2 = 0.0; /* Compute Chi Square */
  for (i = 0; i < K + 1; i++) {
    chi2 += pow((double)nu[i] - (double)N * pi[i], 2) / ((double)N * pi[i]);
    sum += nu[i];
  }
  p_value = cephes_igamc(K / 2.0, chi2 / 2.0);

  printf("    OVERLAPPING TEMPLATE OF ALL ONES TEST\n");
  printf("-----------------------------------------------\n");
  printf("COMPUTATIONAL INFORMATION:\n");
  printf("-----------------------------------------------\n");
  printf("(a) n (sequence_length)      = %d\n", n);
  printf("(b) m (block length of 1s)   = %d\n", m);
  printf("(c) M (length of substring)  = %d\n", M);
  printf("(d) N (number of substrings) = %d\n", N);
  printf("(e) lambda [(M-m+1)/2^m]     = %f\n", lambda);
  printf("(f) eta                      = %f\n", eta);
  printf("-----------------------------------------------\n");
  printf("   F R E Q U E N C Y\n");
  printf("  0   1   2   3   4 >=5   Chi^2   P-value  Assignment\n");
  printf("-----------------------------------------------\n");
  printf("%3d %3d %3d %3d %3d %3d  %f ", nu[0], nu[1], nu[2], nu[3], nu[4],
         nu[5], chi2);

  if (isNegative(p_value) || isGreaterThanOne(p_value))
    printf("WARNING:  P_VALUE IS OUT OF RANGE.\n");

  free(sequence);
  printf("%f %s\n", p_value, p_value < ALPHA ? "FAILURE" : "SUCCESS");

  return p_value;
}

double Pr(int u, double eta) {
  int l;
  double sum, p;

  if (u == 0)
    p = exp(-eta);
  else {
    sum = 0.0;
    for (l = 1; l <= u; l++)
      sum += exp(-eta - u * log(2) + l * log(eta) - cephes_lgam(l + 1) +
                 cephes_lgam(u) - cephes_lgam(l) - cephes_lgam(u - l + 1));
    p = sum;
  }
  return p;
}
