#include "das-c/table.h"

table *alloc_table(const size_t l1, const size_t l2)
{
  table *buffer = (table *)malloc(sizeof(table));
  if (buffer == NULL)
    return NULL;

  buffer->data = (double **)malloc(l1 * sizeof(double *));
  if (buffer->data == NULL)
    return NULL;

  for (size_t i1 = 0; i1 < l1; ++i1)
  {
    if (l2 != 0)
    {
      buffer->data[i1] = (double *)malloc(l2 * sizeof(double));
      if (buffer->data[i1] == NULL)
        return NULL;
    }
    else
      buffer->data[i1] = NULL;
  }

  return buffer;
}

table *change_l2(table *tab, const size_t l2)
{
  for (size_t i1 = 0; i1 < tab->l1; ++i1)
  {
    tab->data[i1] = (double *)realloc(tab->data[i1], l2);
    if (tab->data[i1] == NULL)
      return NULL;
  }

  tab->l2 = l2;
  return tab;
}

void free_table(table *buffer)
{
  for (size_t i1 = 0; i1 < buffer->l1; ++i1)
    free(buffer->data[i1]);
  free(buffer->data);
  free(buffer);
}
