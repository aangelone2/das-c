# ave {#driver-ave}

The `ave` driver allows to compute averages and estimate
the standard error of the mean (SEM) for correlated data
via a blocking procedure.


## Syntax

The call syntax can be printed running the commands

```
$ das ave -h
```

which yields the help message

```
usage: das ave [-h] [-f FIELDS] [-n THREADS] [-o] [-s SKIP] [-v] file

performs binsize scaling

positional arguments:
  file                  file to analyze
options:
  -h, --help            show this help message and exit
  -f FIELDS, --fields FIELDS
                        comma-separated, 1-indexed fields to analyze (default = all)
  -n THREADS            number of threads for parsing process (default = 1)
  -o                    uses OpenMP threading (default = false)
  -s SKIP, --skip SKIP  percentage (1-100) of rows to skip (default = 0)
  -v, --verbose         verbose output
```


## Options guide

- `-f` accepts a comma-separated list of integers,
  representing the fields to parse within the file. *The
  fields are indexed starting from 1 in the option.* If
  not specified, *all* the fields will be parsed.

- `-n` accepts an integer, which will be the number of
  parallel threads spawned to perform file parsing.
  Default value is 1.

- `-o` directs the program to parallelize the parsing
  process using OpenMP threads, rather than the default
  C11 implementation. Default is false.

- `-s` accepts an integer (between 1 and 100), which
  corresponds to the percentage of rows to discard at
  the beginning of the file. Rounding may occur to
  obtain an integer number of rows.

- `-v` will print additional information in the output:
  specifically, `<file> :: <analyzed>/<total> rows ::
  <analyzed> columns`, where the two row numbers are the
  number of analyzed rows and the total number of data
  rows.

The `file` argument should be the path to a plain text
file with the following features:

- Single-space-separated columns. All rows should have
  the same column number.
- Lines beginning with `#`, in any position within the
  file, will be considered as comments and ignored.


## Output

A typical call to `ave` may look like

```
$ das ave -s20 -v -f 1,2,3 resources/11.ave.dat
```

resulting in the output

```
resources/11.ave.dat :: 8192/11430 rows :: 3 columns

1024 8 -4.993957752441e-01 3.1e-04 6.9e-06 -7.249965174927e+00 2.7e-04 5.9e-06 -7.749360951538e+00 1.2e-04 2.7e-06
512 16 -4.993957752441e-01 3.4e-04 1.1e-05 -7.249965174927e+00 2.9e-04 9.1e-06 -7.749360951538e+00 1.3e-04 4.0e-06
256 32 -4.993957752441e-01 3.5e-04 1.6e-05 -7.249965174927e+00 3.0e-04 1.3e-05 -7.749360951538e+00 1.3e-04 5.7e-06
128 64 -4.993957752441e-01 3.4e-04 2.1e-05 -7.249965174927e+00 3.0e-04 1.9e-05 -7.749360951538e+00 1.2e-04 7.6e-06
64 128 -4.993957752441e-01 3.5e-04 3.1e-05 -7.249965174927e+00 3.1e-04 2.7e-05 -7.749360951538e+00 1.2e-04 1.1e-05
```

where the first two columns are the number and size of
bins for each step of the scaling, respectively, while
the following columns represent respectively the mean,
SEM, and SE(SEM) of each of the analyzed columns.

All quantities here are computed as discussed in the
[correlated data](statistics.html#correlated-data)
section of the *Statistical Introduction*.
