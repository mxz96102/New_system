#ifndef UM_SET_FUNCTIONS_H
#define UM_SET_FUNCTIONS_H

#include "set_structs.h"

int set_init(Set **self);
int set_del(Set **self, int (*data_del)(void *data));

int set_search(Set *self, void *data, void **result_data, int *result_found, int (*compar)(const void *, const void *));
int set_insert(Set **self, void *data, int (*compar)(const void *, const void *));
int set_delete(Set **self, void *data, int (*compar)(const void *, const void *));

int set_intersection(Set *set_a, Set *set_b, Set **result_intersection, int (*compar)(const void *, const void *));
int set_union(Set *set_a, Set *set_b, Set **result_union, int (*compar)(const void *, const void *));
int set_extend(Set *set_a, Set *set_b, int (*compar)(const void *, const void *));
int set_difference(Set *set_a, Set *set_b, Set **result_difference, int (*compar)(const void *, const void *));
int set_contract(Set *set_a, Set *set_b, int (*compar)(const void *, const void *));

int set_map(Set *self, void *pipe, int (*callback)(const void *data, void *pipe));

#endif //UM_SET_FUNCTIONS_H
