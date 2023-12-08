#ifndef DAS_C_TABLE_H
#define DAS_C_TABLE_H

#include <stdlib.h>

typedef struct table
{
  const size_t l1;
  size_t l2;
  double **data;
} table;

table *alloc_table(const size_t l1, const size_t l2);

table *change_l2(table *tab, const size_t l2);

void free_table(table *buffer);

#endif
