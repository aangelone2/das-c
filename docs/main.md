# `das-c`

![test](https://img.shields.io/badge/Tests-Passing-32CD32)
[![clang-format](https://img.shields.io/badge/code%20style-clang--format-blue)](https://clang.llvm.org/docs/ClangFormat.html)
[![doxygen](https://img.shields.io/badge/documentation-doxygen-blue)](https://www.doxygen.nl/)


`das-c` (Data Analysis Suite in C) is a data analysis
suite for (Monte Carlo) numerical data.

The suite is designed as a lightweight, multi-threaded
alternative to its [python
counterpart](https://github.com/aangelone2/das),
offering its basic functionalities.




## Dependencies and Setup

The program only requires a version of `gcc` compatible
with the `gnu17` standard. The version used in
development is `13.2.1`.

The command

```bash
$ make build
```

will build the executables `ave` and `avs` in the
`build/` directory. The command

```bash
$ make clean
```

resets the build environment.




## Current capabilities

The capabilities of `das-c` are available by calling the
executables `avs` and `ave`. These include:

- Simple averaging and analysis of uncorrelated data
- Binsize scaling to compute accurate errors for
  correlated data




## Documentation

The command

```bash
$ make docs
```

generates the documentation, which can be viewed opening
in a web browser the generated `html/index.html` file.
