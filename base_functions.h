#ifndef UM_BASE_FUNCTIONS_H
#define UM_BASE_FUNCTIONS_H

#include "base_structs.h"

int base_init(Base **self, void *data);
int base_del(Base **self, int (*data_del)(void *data));

int base_search(Base *self, void *data, void **result_data, int *result_found, int (*compar)(const void *, const void *));
int base_insert(Base **self, void *data, int (*compar)(const void *, const void *));
int base_delete(Base **self, void *data, int *deleted, int (*compar)(const void *, const void *));

int base_map(Base *self, void *pipe, int (*callback)(const void *data, void *pipe));

#endif //UM_BASE_FUNCTIONS_H
