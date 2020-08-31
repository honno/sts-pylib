
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     S T A T I S T I C A L  T E S T  F U N C T I O N  P R O T O T Y P E S
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

double Frequency(unsigned char epsilon[], int n);
double BlockFrequency(unsigned char epsilon[], int M, int n);
double CumulativeSumsForward(unsigned char epsilon[], int n);
double CumulativeSumsBackward(unsigned char epsilon[], int n);
double Runs(unsigned char epsilon[], int n);
double LongestRunOfOnes(unsigned char epsilon[], int n);
double Rank(unsigned char epsilon[], int n);
double DiscreteFourierTransform(unsigned char epsilon[], int n);
double NonOverlappingTemplateMatchings(unsigned char epsilon[], int m, int n);
double OverlappingTemplateMatchings(unsigned char epsilon[], int m, int n);
double Universal(unsigned char epsilon[], int n);
double ApproximateEntropy(unsigned char epsilon[], int m, int n);
double RandomExcursions(unsigned char epsilon[], int n);
double RandomExcursionsVariant(unsigned char epsilon[], int n);
double LinearComplexity(unsigned char epsilon[], int M, int n);
double Serial(unsigned char epsilon[], int m, int n);
