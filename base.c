#include <stdio.h>
#include <stdlib.h>
#include "base_functions.h"


int base_init(Base **self, void *data) {
    Base *temp;
    temp=(Base *)malloc(sizeof(Base));
    if(temp==NULL)
        return 1;

    *self=temp;

    temp->data=data;

    return 0;
}

int base_del(Base **self, int (*data_del)(void *data)) {

}

int base_search(Base *self, void *data, void **result_data, int *result_found, int (*compar)(const void *, const void *)) {

}

int base_insert(Base **self, void *data, int (*compar)(const void *, const void *)) {
    Base *temp,*p1,*p2;
    temp=(Base *)malloc(sizeof(Base));
    if(temp==NULL)
        return 1;

    p1=*self;

    while(p1->next!=NULL)
        p1=p1->next;

    p1->next=temp;
    return 0;

}

int base_delete(Base **self, void *data, int *deleted, int (*compar)(const void *, const void *)) {

}

int base_map(Base *self, void *pipe, int (*callback)(const void *data, void *pipe)) {

}
