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
    Base *p1,p2;
    p1=*self;


}

int base_search(Base *self, void *data, void **result_data, int *result_found, int (*compar)(const void *, const void *)) {
    int flag=1;
    while(self!=NULL){
        flag=(*compar)(self->data,data);
        if(flag==0) {
            result_found=0;
            result_data=self->data;
            return 0;
        }
    }

    result_found=1;

    return 0;
}

int base_insert(Base **self, void *data, int (*compar)(const void *, const void *)) {
    Base *temp,*p1,*p2;
    temp=(Base *)malloc(sizeof(Base));
    if(temp==NULL)
        return 1;

    p1=*self;

    while(p1->next!=NULL) {
        p1 = p1->next;
        if ((*compar)(p1->data, data) == 0)
            return 2;
    }

    p1->next=temp;
    return 0;
}

int base_delete(Base **self, void *data, int *deleted, int (*compar)(const void *, const void *)) {
    Base *p1,*p2;
    p1=*self;
    while ((*compar)(p1->data, data) != 0 && p1 != NULL) {
        p1=p1->next;
    }

    if(p1==self){
       free(p1);
        return 2;
        deleted=0;
    }
    else if(p1!=NULL){
        while(p2->next!=p1){
            p2=p2->next;
        }
        p2->next=p1->next;
        free(p1);
        deleted=0;
    } else deleted=1;

    return 0;
}

int base_map(Base *self, void *pipe, int (*callback)(const void *data, void *pipe)) {
    Base *p1;
    p1 = self->next;
    while (p1 != NULL) {
        if ((*callback)(p1->data, pipe))
            return 1;
        p1 = p1->next;
    }
    return 0;
}

