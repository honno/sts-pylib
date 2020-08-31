from random import getrandbits

from sts import *

def bitseq(n):
    return [getrandbits(1) for _ in range(n)]

def test_monobit():
    assert isinstance(frequency(bitseq(10)), float)

def test_frequency_within_block():
    assert isinstance(block_frequency(bitseq(100), 10), float)

def test_runs():
    assert isinstance(runs(bitseq(10)), float)

def test_cusum_forward():
    assert isinstance(cumulative_sums(bitseq(10)), float)

def test_cusum_backward():
    assert isinstance(cumulative_sums(bitseq(10), reverse=True), float)

def test_longest_runs():
    assert isinstance(longest_run_of_ones(bitseq(160)), float)

def test_binary_matrix_rank():
    assert isinstance(rank(bitseq(1024)), float)

def test_spectral():
    assert isinstance(discrete_fourier_transform(bitseq(10)), float)

def test_non_overlapping_template_matching():
    assert isinstance(non_overlapping_template_matchings(bitseq(20), 2), float)

def test_overlapping_template_matching():
    assert isinstance(overlapping_template_matchings(bitseq(1032), 8), float)

def test_universal():
    assert isinstance(universal(bitseq(387840)), float)

def test_approximate_entropy():
    assert isinstance(approximate_entropy(bitseq(10), 3), float)

def test_random_excursions():
    assert isinstance(random_excursions(bitseq(387840)), float)

def test_random_excursions_variant():
    assert isinstance(random_excursions(bitseq(387840), variant=True), float)

def test_linear_complexity():
    assert isinstance(linear_complexity(bitseq(387840), 8), float)

def test_serial():
    assert isinstance(serial(bitseq(387840), 8), float)

