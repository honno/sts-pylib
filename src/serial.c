#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/cephes.h"
#include "../include/externs.h"

double psi2(unsigned char epsilon[], int m, int n);

double Serial(unsigned char epsilon[], int m, int n) {
  double p_value1, p_value2, psim0, psim1, psim2, del1, del2;

  psim0 = psi2(epsilon, m, n);
  psim1 = psi2(epsilon, m - 1, n);
  psim2 = psi2(epsilon, m - 2, n);
  del1 = psim0 - psim1;
  del2 = psim0 - 2.0 * psim1 + psim2;
  p_value1 = cephes_igamc(pow(2, m - 1) / 2, del1 / 2.0);
  p_value2 = cephes_igamc(pow(2, m - 2) / 2, del2 / 2.0);

  printf("\t       SERIAL TEST\n");
  printf("---------------------------------------------\n");
  printf(" COMPUTATIONAL INFORMATION:		  \n");
  printf("---------------------------------------------\n");
  printf("(a) Block length    (m) = %d\n", m);
  printf("(b) Sequence length (n) = %d\n", n);
  printf("(c) Psi_m               = %f\n", psim0);
  printf("(d) Psi_m-1             = %f\n", psim1);
  printf("(e) Psi_m-2             = %f\n", psim2);
  printf("(f) Del_1               = %f\n", del1);
  printf("(g) Del_2               = %f\n", del2);
  printf("---------------------------------------------\n");

  printf("p_value1 = %f\n", p_value1);
  printf("p_value2 = %f\n", p_value2);

  if (p_value1 < p_value2) {
    return p_value1;
  } else {
    return p_value2;
  }
}

double psi2(unsigned char epsilon[], int m, int n) {
  int i, j, k, powLen;
  double sum, numOfBlocks;
  unsigned int *P;

  if ((m == 0) || (m == -1)) return 0.0;
  numOfBlocks = n;
  powLen = (int)pow(2, m + 1) - 1;
  if ((P = (unsigned int *)calloc(powLen, sizeof(unsigned int))) == NULL) {
    printf("Serial Test:  Insufficient memory available.\n");
    return 0.0;
  }
  for (i = 1; i < powLen - 1; i++) P[i] = 0; /* INITIALIZE NODES */
  for (i = 0; i < numOfBlocks; i++) {        /* COMPUTE FREQUENCY */
    k = 1;
    for (j = 0; j < m; j++) {
      if (epsilon[(i + j) % n] == 0)
        k *= 2;
      else if (epsilon[(i + j) % n] == 1)
        k = 2 * k + 1;
    }
    P[k - 1]++;
  }
  sum = 0.0;
  for (i = (int)pow(2, m) - 1; i < (int)pow(2, m + 1) - 1; i++)
    sum += pow(P[i], 2);
  sum = (sum * pow(2, m) / (double)n) - (double)n;
  free(P);

  return sum;
}
