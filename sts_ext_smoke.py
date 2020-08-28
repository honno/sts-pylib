from math import isclose
from _sts.lib import Frequency

p = Frequency([1, 0, 1, 1, 0, 1, 0, 1, 0, 1], 10)
assert isclose(p, 0.527089, abs_tol=0.005)
