#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/cephes.h"
#include "../include/externs.h"
#include "../include/utilities.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                A P P R O X I M A T E  E N T R O P Y   T E S T
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

double ApproximateEntropy(unsigned char epsilon[], int m, int n) {
  int i, j, k, r, blockSize, seqLength, powLen, index;
  double sum, numOfBlocks, ApEn[2], apen, chi_squared, p_value;
  unsigned int *P;

  printf("\tAPPROXIMATE ENTROPY TEST\n");
  printf("--------------------------------------------\n");
  printf("COMPUTATIONAL INFORMATION:\n");
  printf("--------------------------------------------\n");
  printf("(a) m (block length)    = %d\n", m);

  seqLength = n;
  r = 0;

  for (blockSize = m; blockSize <= m + 1; blockSize++) {
    if (blockSize == 0) {
      ApEn[0] = 0.00;
      r++;
    } else {
      numOfBlocks = (double)seqLength;
      powLen = (int)pow(2, blockSize + 1) - 1;
      if ((P = (unsigned int *)calloc(powLen, sizeof(unsigned int))) == NULL) {
        printf("ApEn:  Insufficient memory available.\n");
        return;
      }
      for (i = 1; i < powLen - 1; i++) P[i] = 0;
      for (i = 0; i < numOfBlocks; i++) { /* COMPUTE FREQUENCY */
        k = 1;
        for (j = 0; j < blockSize; j++) {
          k <<= 1;
          if ((int)epsilon[(i + j) % seqLength] == 1) k++;
        }
        P[k - 1]++;
      }
      /* DISPLAY FREQUENCY */
      sum = 0.0;
      index = (int)pow(2, blockSize) - 1;
      for (i = 0; i < (int)pow(2, blockSize); i++) {
        if (P[index] > 0) sum += P[index] * log(P[index] / numOfBlocks);
        index++;
      }
      sum /= numOfBlocks;
      ApEn[r] = sum;
      r++;
      free(P);
    }
  }
  apen = ApEn[0] - ApEn[1];

  chi_squared = 2.0 * seqLength * (log(2) - apen);
  p_value = cephes_igamc(pow(2, m - 1), chi_squared / 2.0);

  printf("(b) n (sequence length) = %d\n", seqLength);
  printf("(c) Chi^2               = %f\n", chi_squared);
  printf("(d) Phi(m)	       = %f\n", ApEn[0]);
  printf("(e) Phi(m+1)	       = %f\n", ApEn[1]);
  printf("(f) ApEn                = %f\n", apen);
  printf("(g) Log(2)              = %f\n", log(2.0));
  printf("--------------------------------------------\n");

  if (m > (int)(log(seqLength) / log(2) - 5)) {
    printf("Note: The blockSize = %d exceeds recommended value of %d\n", m,
           MAX(1, (int)(log(seqLength) / log(2) - 5)));
    printf("Results are inaccurate!\n");
    printf("--------------------------------------------\n");
  }

  printf("p_value = %f\n", p_value);

  return p_value;
}
