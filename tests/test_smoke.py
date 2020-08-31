from random import getrandbits

from sts import *

def bitseq(n):
    return [getrandbits(1) for _ in range(n)]

def test_monobit():
    assert isinstance(Frequency(bitseq(10), 10), float)

def test_frequency_within_block():
    assert isinstance(BlockFrequency(bitseq(100), 10, 100), float)

def test_cusum_forward():
    assert isinstance(CumulativeSumsForward(bitseq(10), 10), float)

def test_cusum_backward():
    assert isinstance(CumulativeSumsBackward(bitseq(10), 10), float)

def test_runs():
    assert isinstance(Runs(bitseq(10), 10), float)

def test_longest_runs():
    assert isinstance(LongestRunOfOnes(bitseq(160), 160), float)

def test_binary_matrix_rank():
    assert isinstance(Rank(bitseq(1024), 1024), float)

def test_spectral():
    assert isinstance(DiscreteFourierTransform(bitseq(10), 10), float)

def test_non_overlapping_template_matching():
    assert isinstance(NonOverlappingTemplateMatchings(bitseq(20), 2, 20), float)

def test_overlapping_template_matching():
    assert isinstance(OverlappingTemplateMatchings(bitseq(1032), 8, 1032), float)

def test_universal():
    assert isinstance(Universal(bitseq(387840), 387840), float)



