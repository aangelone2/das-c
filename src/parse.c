#include "das-c/table.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define SEPARATOR ' '
#define MAX_LINE_LENGTH 65536

inline bool is_comment(const char *row) { return row[0] == '#'; }

size_t count_cols(const char *row, const char sep)
{
  size_t res = 0;

  for (size_t i = 0; i < strlen(row); ++i)
    if (row[i] == sep)
      ++res;

  return res;
}

int parse_line(table *tab, const char *line)
{
  if (is_comment(line))
    return 0;

  for (size_t col = 0; col < tab->l1; ++col)
  {
    const int ret = sscanf(line, "%lf", &(tab->data[col][tab->l2 - 1]));
    if (ret != 1)
      return 1;
  }

  if (sscanf(line, "%*f") != EOF)
    return 1;

  return 0;
}

table *parse(const char *filename)
{
  FILE *input = fopen(filename, "r");
  if (input == NULL)
    return NULL;

  char line[MAX_LINE_LENGTH];

  size_t total_row = 0;
  do
  {
    ++total_row;

    if (fgets(line, MAX_LINE_LENGTH, input) == NULL)
      return NULL;
  } while (!is_comment(line));

  size_t row = 1;
  const size_t cols = count_cols(line, SEPARATOR);

  table *tab = alloc_table(cols, 0);
  if (tab == NULL)
    return NULL;

  do
  {
    tab = change_l2(tab, tab->l2 + 1);

    if (parse_line(tab, line) != 0)
      return NULL;

    if (fgets(line, MAX_LINE_LENGTH, input) == NULL)
      break;

    ++total_row;
    if (is_comment(line))
      continue;

    ++row;
  } while (true);

  return tab;
}
