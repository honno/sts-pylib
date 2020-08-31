from pathlib import Path
from cffi import FFI
ffi = FFI()

ffi.cdef("double Frequency(unsigned char epsilon[], int n);")
ffi.cdef("double BlockFrequency(unsigned char epsilon[], int M, int n);")
ffi.cdef("double CumulativeSumsForward(unsigned char epsilon[], int n);")
ffi.cdef("double CumulativeSumsBackward(unsigned char epsilon[], int n);")
ffi.cdef("double Runs(unsigned char epsilon[], int n);")
ffi.cdef("double LongestRunOfOnes(unsigned char epsilon[], int n);")
ffi.cdef("double Rank(unsigned char epsilon[], int n);")
ffi.cdef("double DiscreteFourierTransform(unsigned char epsilon[], int n);")
ffi.cdef("double NonOverlappingTemplateMatchings(unsigned char epsilon[], int m, int n);")
ffi.cdef("double OverlappingTemplateMatchings(unsigned char epsilon[], int m, int n);")
ffi.cdef("double Universal(unsigned char epsilon[], int n);")
ffi.cdef("double ApproximateEntropy(unsigned char epsilon[], int m, int n);")
ffi.cdef("double RandomExcursions(unsigned char epsilon[], int n);")
ffi.cdef("double RandomExcursionsVariant(unsigned char epsilon[], int n);")
ffi.cdef("double LinearComplexity(unsigned char epsilon[], int M, int n);")
ffi.cdef("double Serial(unsigned char epsilon[], int m, int n);")

ffi.set_source(
    "_sts",
    """
    #include "../include/stat_fncs.h"
    """,
    sources=[
        "src/frequency.c",
        "src/cephes.c",
        "src/blockFrequency.c",
        "src/cusum.c",
        "src/runs.c",
        "src/longestRunOfOnes.c",
        "src/matrix.c",
        "src/rank.c",
        "src/dfft.c",
        "src/discreteFourierTransform.c",
        "src/nonOverlappingTemplateMatchings.c",
        "src/overlappingTemplateMatchings.c",
        "src/universal.c",
        "src/approximateEntropy.c",
        "src/randomExcursions.c",
        "src/randomExcursionsVariant.c",
        "src/linearComplexity.c",
        "src/serial.c",
    ],
    include_dirs=["include/"],
)

if __name__ == "__main__":
    ffi.compile(verbose=True)
