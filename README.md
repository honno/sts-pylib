# sts-pylib

![GitHub Workflow Status](https://img.shields.io/github/workflow/status/Honno/sts-pylib/Test%20package)
![Read the Docs](https://img.shields.io/readthedocs/sts-pylib)
![License](https://img.shields.io/badge/license-public%20domain-informational)
![PyPI](https://img.shields.io/pypi/v/sts-pylib)
![Python Version](https://img.shields.io/badge/python-3.6%2B-informational)

A functional Python interface to the NIST Statistical Test Suite.

## Quickstart

You can install `sts-pylib` via `pip`:

```console
$ pip install sts-pylib
```

This will install a package `sts` into your system,
which contains NIST's statistical tests for randomness.
A complete reference is available in the [docs](https://sts-pylib.readthedocs.io/en/latest/).

```pycon
>>> import sts
>>> p_value = sts.frequency([1, 0, 1, 1, 0, 1, 0, 1, 0, 1])
	      FREQUENCY TEST
---------------------------------------------
COMPUTATIONAL INFORMATION:
(a) The nth partial sum = 2
(b) S_n/n               = 0.200000
---------------------------------------------
p_value = 0.527089
>>> print(p_value)
0.5270892568655381
```

Note that all the tests take the input sequence `epsilon`
(a sample of RNG output)
as an array of `0` and `1` integers.

## Contributors

The [original sts C program](https://csrc.nist.gov/Projects/Random-Bit-Generation/Documentation-and-Software),
alongside its corresponding [SP800-22 paper](https://csrc.nist.gov/publications/detail/sp/800-22/rev-1a/final),
were authored by the following at [NIST](https://www.nist.gov/):

* Andrew Rukhin
* Juan Soto
* James Nechvatal
* Miles Smid
* Elaine Barker
* Stefan Leigh
* Mark Levenson
* Mark Vangel
* David Banks,
* Alan Heckert
* James Dray
* San Vo
* Lawrence E Bassham III

Additional work to improve Windows compatibility was done by
Paweł Krawczyk ([@kravietz](https://github.com/kravietz)),
with a bug fix by [@ZZMarquis](https://github.com/ZZMarquis).

I ([@Honno](https://github.com/Honno)) am responsible for
converting sts into a functional interface,
and providing a Python wrapper on-top of it.
You can check out my own randomness testing suite [coinflip](https://github.com/Honno/coinflip/),
where I am creating a robust and user-friendly
version of NIST's sts in Python.
