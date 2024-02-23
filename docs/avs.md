# avs {#driver-avs}

The `avs` driver allows to analyze uncorrelated data, by
computing averages, standard errors of the mean (SEM),
and standard deviation of the SEM for multi-column data
files.


## Syntax

The call syntax can be printed running the commands

```
$ das avs -h
```

which yields the help message

```
usage: das avs [-h] [-f FIELDS] [-n THREADS] [-o] [-s SKIP] [-v] file

performs averages without rebinning

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

A typical call to `avs` may look like

```
$ das avs -s20 -v -f 1,2,3 resources/10.avs.dat
```

resulting in the output

```
resources/10.avs.dat :: 2606/3257 rows :: 3 columns

0 +5.151493365490e-01 5.6e-03
1 +4.957831770435e-01 5.6e-03
2 +4.985958686429e-01 5.7e-03
```

where each row contains the statistical results for one
of the columns of the data set.

All quantities here are defined as discussed in the
[uncorrelated data](statistics.html#uncorrelated-data)
section of the *Statistical Introduction*.
