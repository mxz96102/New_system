#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sns_functions.h"
#include "set_functions.h"
#include "cJSON.h"

int id_cmp(People *data1,People *data2);

int delete(void *aim);

int id_all_get(People *data, int **p);

int count(void *data, int *p);

// sns
int sns_json_file_read(Sns **self, char *filename){
    FILE *fp;
    int i = 0, id, childid;
    int sum, j, k;
    char *str, *s;
    cJSON *root, *layer1, *layer2;
    People *temp_man, *aim1, *aim2;

    sns_init(self);
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("file error");
        return 1;
    }
    fseek(fp, 0, SEEK_END);
    unsigned len = ftell(fp);
    s = (char *) malloc(len + 1);
    rewind(fp);
    fread(s, 1, len, fp);
    s[len] = 0;
    root = cJSON_Parse(s);
    if (!root)
        printf("parse error");
    sum = cJSON_GetArraySize(root);
    while (i < sum && sum != 0) {
        layer1 = cJSON_GetArrayItem(root, i);
        layer2 = cJSON_GetObjectItem(layer1, "name");
        str = layer2->valuestring;
        layer2 = cJSON_GetObjectItem(layer1, "id");
        id = layer2->valueint;
        people_init(*self, &temp_man, str, id, id);
        sns_insert_people(*self, temp_man, id);
        i++;
    }
    k = 0;
    sum = cJSON_GetArraySize(root);
    while (k < sum) {
        i = 0;
        layer1 = cJSON_GetArrayItem(root, i);
        layer2 = cJSON_GetObjectItem(layer1, "followings");
        j = cJSON_GetArraySize(layer2);
        id = cJSON_GetObjectItem(layer1, "id")->valueint;
        while (i < j) {
            childid = (cJSON_GetArrayItem(layer2, i)->valueint);
            sns_search_people(*self, id, &aim1);
            sns_search_people(*self, childid, &aim2);
            people_follow(aim1, aim2);
            i++;
        }
        layer2 = cJSON_GetObjectItem(layer1, "friends");
        j = cJSON_GetArraySize(layer2);
        i = 0;
        while (i < j) {
            childid = cJSON_GetArrayItem(layer2, i)->valueint;
            sns_search_people(*self, id, &aim1);
            sns_search_people(*self, childid, &aim2);
            people_friend(aim1, aim2);
            i++;
        }
        k++;
    }
    fclose(fp);
    cJSON_Delete(root);
    return 0;
}

int sns_json_file_write(Sns *self, char *filename){
    FILE *fp;
    cJSON *root, *layer1, *layer2;
    char *str;
    int id = 1, f[255] = {0}, num = 0, flag, *p;
    People *temp_man, *aim1, *aim2;
    Circle *cir;

    fp = fopen(filename, "w");
    root = cJSON_CreateArray();
    while (id <= self->peoples_id_max) {
        flag = sns_search_people(self, id, &temp_man);
        layer1 = cJSON_CreateObject();
        cJSON_AddItemToArray(root, layer1);\
        cJSON_AddNumberToObject(layer1, "id", temp_man->id);
        cJSON_AddStringToObject(layer1, "name", temp_man->name);
        people_followings(temp_man, &cir);
        p = f;
        num = 0;
        circle_map_people(cir, &p, (int (*)(const void *, void *)) id_all_get);
        circle_map_people(cir, &num, (int (*)(const void *, void *)) count);
        layer2 = cJSON_CreateIntArray(f, num);
        cJSON_AddItemToObject(layer1, "followings", layer2);
        people_friends(temp_man, &cir);
        p = f;
        num = 0;
        circle_map_people(cir, &p, (int (*)(const void *, void *)) id_all_get);
        circle_map_people(cir, &num, (int (*)(const void *, void *)) count);
        layer2 = cJSON_CreateIntArray(f, num);
        cJSON_AddItemToObject(layer1, "friends", layer2);
        id++;
    }
    str = cJSON_Print(root);
    printf("%s", str);
    fputs(str, fp);
    fclose(fp);
    cJSON_Delete(root);
    return 0;
}

int sns_init(Sns **self){
    Sns *temp;
    Set *people;
    temp = (Sns *) malloc(sizeof(Sns));
    if (temp == NULL)
        return 1;
    set_init(&people);
    temp->peoples_id_max = 0;
    temp->_peoples = people;
    *self = temp;

    return 0;
}

int sns_del(Sns **self){
    set_del(&(*self)->_peoples, delete);
    return 0;
}

int sns_search_people(Sns *self, int id, People **result_people){
    People *data, *result;
    int respond, flag;
    people_init(self, &data, "NULL", id, id);
    flag = set_search(self->_peoples, data, (void **) &result, &respond, (int (*)(const void *, const void *)) id_cmp);
    *result_people = result;
    return flag;
}
int sns_insert_people(Sns *self, People *people, int id_given){
    int flag;
    if (id_given <= self->peoples_id_max)
        return 2;
    flag = set_insert(&(self->_peoples), people, (int (*)(const void *, const void *)) id_cmp);
    self->peoples_id_max++;
    if (flag)
        return 1;
    else
        return 0;
}
int sns_delete_people(Sns *self, People *people){
    int flag;
    flag = set_delete(&self->_peoples, people, (int (*)(const void *, const void *)) id_cmp);
    return flag;
}

int sns_map_people(Sns *self, void *pipe, int (*callback)(const void *data, void *pipe)){
    int flag = 1;
    flag = set_map(self->_peoples, pipe, *callback);
    return flag;
}

// people
int people_init(Sns *universal, People **self, char name[100], int id, int id_given){
    Set *temp;
    People *new_man;
    new_man = (People *) malloc(sizeof(People));
    if (new_man == NULL)
        return 1;
    set_init(&new_man->_followings);
    set_init(&new_man->_friends);
    set_init(&new_man->_followers);
    set_init(&new_man->__incoming_friends);
    strcpy(new_man->name, name);
    new_man->id = id;
    *self = new_man;
    return 0;
}

int people_del(Sns *universal, People **self){
    return 0;
}

int people_patch(People *self, char name[100], int id){
    strcpy(self->name, name);
    return 0;
}

int people_follow(People *self, People *target){
    int flag[2];
    flag[2] = set_insert(&(self->_followings), target, (int (*)(const void *, const void *)) id_cmp);
    flag[1] = set_insert(&(target->_followers), self, (int (*)(const void *, const void *)) id_cmp);
    if (flag[1] || flag[2])
        return 1;
    else
        return 0;
}
int people_unfollow(People *self, People *target){
    int flag[2];
    flag[2] = set_delete(&(self->_followings), target, (int (*)(const void *, const void *)) id_cmp);
    flag[1] = set_delete(&(target->_followers), self, (int (*)(const void *, const void *)) id_cmp);
    if (flag[1] || flag[2])
        return 1;
    else
        return 0;
}
int people_friend(People *self, People *target){
    int flag;
    flag = set_insert(&(self->_friends), target, (int (*)(const void *, const void *)) id_cmp);
    if (flag)
        return 1;
    else
        return 0;

}
int people_unfriend(People *self, People *target){
    int flag;
    flag = set_delete(&(self->_friends), target, (int (*)(const void *, const void *)) id_cmp);
    if (flag)
        return 1;
    else
        return 0;
}

int people_followings(People *self, Circle **followings){
    *(followings) = (Circle *) malloc(sizeof(Circle));
    (*followings)->_peoples = self->_followings;
    return 0;
}

int people_followers(People *self, Circle **followers){
    (*followers) = (Circle *) malloc(sizeof(Circle));
    (*followers)->_peoples = self->_followers;
    return 0;
}

int people_friends(People *self, Circle **friends){
    (*friends) = (Circle *) malloc(sizeof(Circle));
    (*friends)->_peoples = self->_followings;
    return 0;
}

int people_common_followings(People *self, People *target, Circle **common_followings){
    int flag;
    *common_followings = (Circle *) malloc(sizeof(Circle));
    flag = set_intersection(self->_followings, target->_followings, &((*common_followings)->_peoples),
                            (int (*)(const void *, const void *)) id_cmp);
    return flag;
}

int people_common_followers(People *self, People *target, Circle **common_followers){
    int flag;
    *common_followers = (Circle *) malloc(sizeof(Circle));
    flag = set_intersection(self->_followers, target->_followers, &((*common_followers)->_peoples),
                            (int (*)(const void *, const void *)) id_cmp);
    return flag;
}

int people_extend_friends(People *self, Circle **extend_friends){
    *extend_friends = (Circle *) malloc(sizeof(Circle));
    return 0;
}

// circle

int circle_map_people(Circle *self, void *pipe, int (*callback)(const void *data, void *pipe)){
    int flag = 1;
    flag = set_map(self->_peoples, pipe, *callback);
    return flag;
}


int id_cmp(People *data1,People *data2){
    if (data1->id==data2->id)
        return 0;
    else
        return 1;
}

int id_all_get(People *data, int **p) {
    **p = data->id;
    (*p)++;
    return 0;
}

int count(void *data, int *p) {
    (*p)++;
    return 0;
}




