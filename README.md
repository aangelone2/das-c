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

```
$ make test
```

will build the static library against which the program
will compile, as well as a battery of tests which will
be immediately executed. When successfully completed,
the output of this command should have the form

```
<compilation logs>

Beginning testing

cd build/ ; ./01.test-count_fields
  <testing logs>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test completed successfully

...

All tests completed successfully
```

Independently from the testing command, the command

```
$ make build
```

will build the `build/das` executable and the static
library the latter will link to.

The command

```
$ make clean
```

resets the build environment.




## Current capabilities

The capabilities of `das-c` are programmed in *drivers*,
subcommands specialized for a specific task, and
include:

- Simple averaging and analysis of uncorrelated data
  (`avs`);
- Binsize scaling to compute accurate errors for
  correlated data (`ave`).

Each driver is invoked as

```
$ das <driver> <options/arguments>
```

Executing any driver with the `-h` option will display a
help message and exit.




## Documentation

Building the documentation requires
[doxygen](https://www.doxygen.nl/). The command

```
$ make docs
```

re-generates the documentation in html format in the
`html/` directory, which can be accessed by opening in a
web browser the `html/index.html` page.

Most of the documentation (including all the information
related to the UI and the statistical background) can be
consulted on the [github
wiki](https://github.com/aangelone2/das-c/wiki).
