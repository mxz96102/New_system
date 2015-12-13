#include <stdio.h>
#include <stdlib.h>
#include "set_functions.h"
#include "base_functions.h"


int set_inc(void *data, Set *p);

int set_compar(void *data1, void *data2);

int set_1(void *data1, void *data2);

int set_uni(void *data, Set *p);

int set_copy(void *data, Set *p);

int set_dif(void *data, Set *p);

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
    data_del(*self);
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
    Set *temp_a, *temp_b, *temp_c;
    void *data;
    int flag;
    data = NULL;
    flag = set_init(&temp_a);
    flag += set_init(&temp_b);
    flag += set_init(&temp_c);
    flag += base_map(set_a->_base, temp_a, (int (*)(const void *, void *)) set_copy);
    flag += base_map(set_b->_base, temp_b, (int (*)(const void *, void *)) set_copy);
    flag += base_map(set_b->_base, temp_a, (int (*)(const void *, void *)) set_dif);
    flag += base_map(set_a->_base, temp_b, (int (*)(const void *, void *)) set_dif);
    flag += base_map(temp_a->_base, temp_b, (int (*)(const void *, void *)) set_uni);
    flag += base_map(set_a->_base, temp_c, (int (*)(const void *, void *)) set_copy);
    flag += base_map(temp_b->_base, temp_c, (int (*)(const void *, void *)) set_dif);
    *result_intersection = temp_c;
    return flag;
}

int set_inc(void *data, Set *p) {
    int flag;
    flag = base_map(p->_base, data, (int (*)(const void *, void *)) set_compar);
    if (flag == 0) {
        set_delete(&p, data, (int (*)(const void *, const void *)) set_compar);
    }
    return 0;
}

int set_union(Set *set_a, Set *set_b, Set **result_union, int (*compar)(const void *, const void *)){
    Set *temp;
    int flag;
    void *data;
    temp = (Set *) malloc(sizeof(Set));
    if (temp == NULL)
        return 1;
    base_init(&temp->_base, data);
    flag = base_map(set_a->_base, &temp, (int (*)(const void *, void *)) set_copy);
    flag += set_map(set_b, temp, (int (*)(const void *, void *)) set_uni);
    *result_union = temp;
    return flag;
}


int set_uni(void *data, Set *p) {
    int flag;
    flag = set_map(p, data, (int (*)(const void *, void *)) set_compar);
    if (flag) {
        set_insert(&p, data, (int (*)(const void *, const void *)) set_compar);
    }
    return 0;
}

int set_extend(Set *set_a, Set *set_b, int (*compar)(const void *, const void *)){
    Set *temp;
    int flag;
    void *data;
    temp = (Set *) malloc(sizeof(Set));
    if (temp == NULL)
        return 1;
    base_init(&temp->_base, data);
    flag = set_map(set_a, set_b, (int (*)(const void *, void *)) set_uni);
    return flag;
}

int set_difference(Set *set_a, Set *set_b, Set **result_difference, int (*compar)(const void *, const void *)){
    int flag;
    Set *temp;
    void *data;
    temp = (Set *) malloc(sizeof(Set));
    if (temp == NULL)
        return 1;
    base_init(&temp->_base, data);
    flag = set_init(&temp);
    flag += base_map(set_a->_base, temp, (int (*)(const void *, void *)) set_copy);
    flag += set_map(set_b, temp, (int (*)(const void *, void *)) set_dif);
    *result_difference = temp;
    return flag;
}


int set_dif(void *data, Set *p) {
    int flag;
    flag = base_map(p->_base, data, (int (*)(const void *, void *)) set_compar);
    if (flag) {
        set_delete(&p, data, (int (*)(const void *, const void *)) set_compar);
    }
    return 0;
}

int set_contract(Set *set_a, Set *set_b, int (*compar)(const void *, const void *)){
    Set *temp;
    int flag;
    void *data;
    temp = (Set *) malloc(sizeof(Set));
    if (temp == NULL)
        return 1;
    base_init(&temp->_base, data);
    flag = set_map(set_a, set_b, (int (*)(const void *, void *)) set_dif);
    return flag;
}

int set_map(Set *self, void *pipe, int (*callback)(const void *data, void *pipe)){
    int flag;
    flag = base_map(self->_base, pipe, *callback);
    return flag;
}

int set_copy(void *data, Set *p) {
    set_insert(&p, data, (int (*)(const void *, const void *)) set_1);
    return 0;
}

int set_compar(void *data1, void *data2) {
    if (data1 == data2)
        return 1;
    else
        return 0;
}

int set_1(void *data1, void *data2) {
    return 1;
}