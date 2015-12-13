#include <stdio.h>
#include <stdlib.h>
#include "set_functions.h"
#include "base_functions.h"


int set_copy(void *data, Set **p);

int set_inc(void *data, Set *p);

int set_compar(void *data1, void *data2);

int set_init(Set **self){
    Set *temp;
    temp=(Set *)malloc(sizeof(Set));
    if(temp==NULL)
        return 1;
    *self=temp;
    (*self)->size = 0;
    base_init(&(temp->_base), NULL);
    return 0;
}

int set_del(Set **self, int (*data_del)(void *data)){
    int flag;
    flag = base_del(&(*self)->_base, data_del);
    return flag;
}

int set_search(Set *self, void *data, void **result_data, int *result_found, int (*compar)(const void *, const void *)){
    int flag;
    flag=base_search(self->_base,data,result_data,result_found,compar);
    return flag;
}

int set_insert(Set **self, void *data, int (*compar)(const void *, const void *)){
    int flag;
    flag = base_insert(&(*self)->_base, data, compar);
    (*self)->size++;
    return flag;
}
int set_delete(Set **self, void *data, int (*compar)(const void *, const void *)){
    int result;
    base_delete(&(*self)->_base, data, &result, compar);
    (*self)->size--;
    return result;
}

int set_intersection(Set *set_a, Set *set_b, Set **result_intersection, int (*compar)(const void *, const void *)){
    Set *temp;
    void *data;
    int flag;
    data = NULL;
    flag = set_init(&temp);
    flag += base_init(&temp->_base, data);
    flag += base_map(set_a->_base, &(temp->_base), (int (*)(const void *, void *)) set_copy);
    flag += set_map(set_b, temp, (int (*)(const void *, void *)) set_inc);
    *result_intersection = temp;
    return flag;
}

int set_union(Set *set_a, Set *set_b, Set **result_union, int (*compar)(const void *, const void *)){
    Set *temp;
    void *data;
    temp = (Set *) malloc(sizeof(Set));
    if (temp == NULL)
        return 1;
    base_init(&temp->_base, data);
}

int set_extend(Set *set_a, Set *set_b, int (*compar)(const void *, const void *)){
    Set *temp;
    void *data;
    temp = (Set *) malloc(sizeof(Set));
    if (temp == NULL)
        return 1;
    base_init(&temp->_base, data);
}

int set_difference(Set *set_a, Set *set_b, Set **result_difference, int (*compar)(const void *, const void *)){
    Set *temp;
    void *data;
    temp = (Set *) malloc(sizeof(Set));
    if (temp == NULL)
        return 1;
    base_init(&temp->_base, data);
}

int set_contract(Set *set_a, Set *set_b, int (*compar)(const void *, const void *)){
    Set *temp;
    void *data;
    temp = (Set *) malloc(sizeof(Set));
    if (temp == NULL)
        return 1;
    base_init(&temp->_base, data);
}

int set_map(Set *self, void *pipe, int (*callback)(const void *data, void *pipe)){
    int flag;
    flag = base_map(self->_base, pipe, *callback);
    return flag;
}

int set_copy(void *data, Set **p) {
    set_insert(p, data, (int (*)(const void *, const void *)) 0);
    return 0;
}

int set_compar(void *data1, void *data2) {
    if (data1 == data2)
        return 1;
    else return 0;
}

int set_inc(void *data, Set *p) {
    int flag;
    flag = set_map(p, data, (int (*)(const void *, void *)) set_compar);
    if (!flag) {
        set_delete(&p, data, (int (*)(const void *, const void *)) set_compar);
    }
    return 0;
}