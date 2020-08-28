from pathlib import Path
from cffi import FFI
ffi = FFI()

ffi.cdef("double Frequency(unsigned char epsilon[], int n);")

ffi.set_source(
    "_sts",  # name of the output C extension
    """
    #include "include/stat_fncs.h"
    """,
    sources=["src/frequency.c"],
    include_dirs=["include/"],
)

if __name__ == "__main__":
    ffi.compile(verbose=True)
