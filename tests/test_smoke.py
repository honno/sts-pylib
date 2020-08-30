from random import getrandbits

from sts import *

def bitseq(n):
    return [getrandbits(1) for _ in range(n)]

def test_monobit():
    assert Frequency(bitseq(10), 10)

def test_frequency_within_block():
    assert BlockFrequency(bitseq(100), 10, 100)

def test_cusum_forward():
    assert CumulativeSumsForward(bitseq(10), 10)

def test_cusum_backward():
    assert CumulativeSumsBackward(bitseq(10), 10)

def test_runs():
    assert Runs(bitseq(10), 10)

def test_longest_runs():
    assert LongestRunOfOnes(bitseq(160), 160)

