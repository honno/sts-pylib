from setuptools import setup

setup(
    name="sts-pylib",
    description="NIST's Statistical Test Suite bindings",
    long_description=open("README.md").read(),
    long_description_content_type="text/markdown",
    author="Matthew Barber",
    py_modules=["sts"],
    cffi_modules=["ext_build.py:ffi"],
    install_requires=["cffi>=1.0.0"],
    setup_requires=["cffi>=1.0.0"],
)
