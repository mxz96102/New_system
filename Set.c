#include <stdio.h>
#include <stdlib.h>
#include "set_functions.h"
#include "base_functions.h"


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
    data = NULL;
    temp=(Set *)malloc(sizeof(Set));
    if(temp==NULL)
        return 1;
    base_init(&temp->_base, data);


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

