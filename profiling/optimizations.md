# General Considerations

Optimization was started at `200e6ad`; the library and
main executable was compiled with `-O3` replaced by the
`-pg` option, and the profiling results in
`profiling/log-01.log` were obtained by running the
commands

```
$ time ../build/das ave -s20 -v 11.large.dat
$ gprof ../build/das gmon.out > out-01.log
```

in the `resources/` folder, where `11.large.dat` is a
4x8e7 datafile created by the `11.generator.py` python
script. The overall execution time is ~47s.

In the results, the following functions (and their
children) took the largest share of the execution time:

- `main()` (92.7 %)
- `parse()` (75.2 %)
- `parse_line()` (69.0 %)
- `push_back()` (25.5 %)
- `rebin()` (14.8 %)

The main data structure of the program is `table`, which
essentially holds an array of pointers to `vector`
structures, each wrapping a `double` array. Each of the
`vector`s is associated to one of the columns of the
datafile.

Schematically, the program works as follows:

- The first non-commented line is tokenized and parsed,
  to compute the number of fields.
- The file is read, line-by-line, with the overall
  number of lines being unknown.
- Lines are screened for commented ones.
- Each non-commented line is tokenized and checked for
  field number and validity.
- Each parsed value in a row is pushed back (with
  possible reallocations) in one of the `vector`s
  contained within the main `table`.
- When parsing is finished, each of the columns is
  rebinned and analyzed independently.

From the profiling, we can deduce that the parsing
process (by and large, including reallocations and such)
is the main bottleneck, and should therefore be the
primary target of optimization. Possible directions to
change the code may be:

1. Replacing line tokenization with simple parsing of
   the required amount of numerical fields. This amount
   can be cheaply computed by tokenizing the first line,
   and does not need to be passed by the user as
   additional information.

   However, this approach would require guaranteeing
   that all lines have the exact required amount of
   fields, and that all entries are valid floating-point
   numbers. This may not be realistically possible,
   especially for very large files. As such,
   tokenization and dynamic field checking will be
   maintained.

2. Pre-computing the number of rows instead of
   dynamically adding components to each of the
   `vector`s in the `table`. This information could be
   passed by the user (computed through efficient tools
   such as `wc`) or computed using an in-house function,
   using either `fgetc()` or `fgets` to discard lines
   until computed (whichever solution is faster).
   In-house functions could also be extended to skip
   commented lines when counting, fully recovering
   current functionality.

   This solution would require determining which of the
   two counting approaches is better, and may not be
   worth it if the execution time share of the counting
   process is ~25% of the execution time (the amount
   spent pushing back and possibly reallocating). `wc`
   takes ~3s to count the number of lines, compared to a
   projected ~10s for the `push_back()` routine from the
   profiling, making this direction worth investigating.

3. Transposing the data structure, rearranging `table`
   as an array of rows, rather than an array of columns.
   This would simplify the code massively, since the
   `vector` data type would be made superfluous, and
   `table` would only wrap a `double **` array with
   fixed inner size.

   The outer size may be declared in advance (as in
   point (2)) or be subject to reallocation (being a
   `double *` array, reallocation should be cheaper, and
   it should happen statistically `N` times less than
   previously, where `N` is the number of columns).

   The transposition should lead to less cache issues
   during parsing, since all the value read in a single
   line will be saved in a single array, which can be
   loaded in memory in one go (instead of requiring the
   loading of multiple column arrays, one component of
   which is changed at a time).

   In turn, more reads will be needed in the statistical
   functions; the best possible way to rearrange them is
   to write functions which accept a `table` object,
   analyzing all the columns at once and using
   array-sized buffers to accumulate statistics. The
   statistical functions are much easier to parallelize
   (see below), which could counteract this.




# Transposition

We applied the modification discussed in point (3)
above. We immediately noticed that it led to a
simplification of the codebase (except for slightly more
complex statistical functions). Profiling results are
displayed in `profiling/log-02.log`, for an overall
execution time of ~41s, slightly shorter than the
original version.

In the results, the following functions (and their
children) took the largest share of the execution time:

- `main()` (94.1 %)
- `parse()` (78.6 %)
- `parse_line()` (72.4 %)
- `rebin()` (15.0 %)
- `add_row()` (14.8 %)

These times have been roughly verified by selectively
disabling parts of the code: the parsing routine without
statistical functions, `add_row()` (`parse.c:40`) and
data writing (`ave.c:58`) took ~36s (~88%) of the time,
while only removing the data writing did not result in
appreciable differences.

Due to the new data structure, fewer allocations
(performed in `add_row()`) need to take place. The
statistical functions remain as irrelevant as they were
before, doubling down on the necessity to optimize or
parallelize parsing. Performance improvements have
appeared, albeit not extremely large.
