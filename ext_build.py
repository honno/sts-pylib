from pathlib import Path
from cffi import FFI
ffi = FFI()

ffi.cdef("double Frequency(unsigned char epsilon[], int n);")
ffi.cdef("double BlockFrequency(unsigned char epsilon[], int M, int n);")
ffi.cdef("double CumulativeSumsForward(unsigned char epsilon[], int n);")
ffi.cdef("double CumulativeSumsBackward(unsigned char epsilon[], int n);")
ffi.cdef("double Runs(unsigned char epsilon[], int n);")
ffi.cdef("double LongestRunOfOnes(unsigned char epsilon[], int n);")

ffi.set_source(
    "_sts",
    """
    #include "../include/stat_fncs.h"
    """,
    sources=["src/frequency.c",
             "src/cephes.c",
             "src/blockFrequency.c",
             "src/cusum.c",
             "src/runs.c",
             "src/longestRunOfOnes.c"],
    include_dirs=["include/"],
)

if __name__ == "__main__":
    ffi.compile(verbose=True)
