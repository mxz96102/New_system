#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sns_functions.h"

Sns *global;
int all_id = 1;

int get_all_name(People *data, char *name);

int add_following();

int del_friend();

int del_following();

int common_followings();

int common_followers();

int extend_friends();

int add_friend();

int User_create();

int User_delete();

int User_information();

int File_Load();

int File_Save();

int menu();

int File();

int User();

int Sns_o();

char *itoa(int num, char *str, int radix);

int main(void) {
    int option = 1;
    sns_init(&global);
    while (option != 9) {
        option = menu();
        switch (option) {
            case 1:
                option = File();
                break;
            case 2:
                option = User();
                break;
            case 3:
                option = Sns_o();
                break;
            case 4:
            default:
                break;
        }
    }
}

int menu() {
    int option = 1;
    printf("\n################\n");
    printf("#\tUser system:\n");
    printf("#1.File operation\n");
    printf("#2.User operation\n");
    printf("#3.Sns operation\n");
    printf("################\n");
    printf("\nwhat do you want to do: ");
    fflush(stdin);
    fscanf(stdin, "%1d", &option);
    return option;
}

int File() {
    int option = 1, flag = 1;
    printf("\n################\n");
    printf("#\tFile operation:\n");
    printf("#1.File Load\n");
    printf("#2.File Save\n");
    printf("#3.Back to main\n");
    printf("################\n");
    printf("\nwhat do you want to do: ");
    while (option != 3 && flag != 0) {
        fflush(stdin);
        fscanf(stdin, "%1d", &option);
        switch (option) {
            case 1:
                flag = File_Load();
                break;
            case 2:
                flag = File_Save();
                break;
            case 3:
                break;
            default:
                break;
        }
    }
    return 0;
}

int File_Save() {
    int flag;
    char file_name[255];
    printf("\nFile name:  ");
    fflush(stdin);
    fscanf(stdin, "%s", file_name);
    flag = sns_json_file_write(global, file_name);
    return flag;
}

int File_Load() {
    int flag;
    char file_name[255];
    printf("\nFile name:  ");
    fscanf(stdin, "%s", file_name);
    flag = sns_json_file_read(&global, file_name);
    return flag;
}

int User() {
    int option = 1, flag = 1;
    printf("\n################\n");
    printf("#\tUser operation\n");
    printf("#1.User create\n");
    printf("#2.User information\n");
    printf("#3.User delete\n");
    printf("#4.Back to menu\n");
    printf("################\n");
    printf("\nwhat do you want to do: ");
    while (option != 4 && flag != 0) {
        fflush(stdin);
        fscanf(stdin, "%1d", &option);
        switch (option) {
            case 1:
                flag = User_create();
                break;
            case 2:
                flag = User_information();
                break;
            case 3:
                flag = User_delete();
                break;
            case 4:
                break;
            default:
                break;
        }
    }
    return 0;
}

int User_create() {
    int flag;
    People *user;
    char user_name[100];
    printf("please write your name: ");
    fflush(stdin);
    fscanf(stdin, "%s", user_name);
    flag = people_init(global, &user, user_name, all_id, all_id);
    all_id++;
    flag += sns_insert_people(global, user, user->id);
    return flag;
}

int User_information() {
    int flag, id;
    char temp[1000] = {""};
    People *aim;
    Circle *cir;
    void *callback;
    printf("please tell me the id you're looking for: ");
    fflush(stdin);
    fscanf(stdin, "%d", &id);
    flag = sns_search_people(global, id, &aim);
    if (flag) {
        printf("404 NOT FOUND\n");
        return 1;
    } else {
        callback = get_all_name;
        printf("Id:%d\n", aim->id);
        printf("Name:%s\n", aim->name);

        people_followings(aim, &cir);
        strcpy(temp, " ");
        flag = circle_map_people(cir, temp, callback);
        if (!flag)
            printf("followings:%s \n", temp);

        people_followers(aim, &cir);
        strcpy(temp, " ");
        circle_map_people(cir, temp, callback);
        if (!flag)
            printf("followers:%s\n", temp);

        people_friends(aim, &cir);
        strcpy(temp, " ");
        circle_map_people(cir, temp, callback);
        if (!flag)
            printf("friends:%s\n", temp);
    }
    return 0;
}

int User_delete() {
    int flag, id;
    People *aim;
    printf("please tell me the id you want to delete: ");
    fflush(stdin);
    fscanf(stdin, "%d", &id);
    flag = sns_search_people(global, id, &aim);
    if (flag) {
        printf("404 NOT FOUND\n");
        return 1;
    } else {
        flag = sns_delete_people(global, aim);
    }
    return flag;
}

int Sns_o() {
    int option = 1, flag = 1;
    printf("\n################\n");
    printf("#\tSns operation:\n");
    printf("#1.User1 add user2 as friend.\n");
    printf("#2.User1 add user2 as following.\n");
    printf("#3.User1 delete user2 as friend.\n");
    printf("#4.User1 delete user2 as following.\n");
    printf("#5.Find common followings of user1 and user2.\n");
    printf("#6.Find common followers of user1 and user2.\n");
    printf("#7.Find extend friends of user1\n");
    printf("#8.Back to main\n");
    printf("################\n");
    printf("\nwhat do you want to do: ");
    while (option != 8 && flag != 0) {
        fscanf(stdin, "%1d", &option);
        switch (option) {
            case 1:
                flag = add_friend();
                break;
            case 2:
                flag = add_following();
                break;
            case 3:
                flag = del_friend();
                break;
            case 4:
                flag = del_following();
                break;
            case 5:
                flag = common_followings();
                break;
            case 6:
                flag = common_followers();
                break;
            case 7:
                flag = extend_friends();
                break;
            case 8:
                break;
            default:
                break;
        }
    }
    return 0;
}

int add_friend() {
    int flag, id1, id2;
    People *aim1, *aim2;
    printf("please tell me the user1 id: ");
    fflush(stdin);
    fscanf(stdin, "%d", &id1);
    printf("please tell me the user2 id: ");
    fflush(stdin);
    fscanf(stdin, "%d", &id2);
    flag = sns_search_people(global, id1, &aim1);
    if (flag) {
        printf("404 NOT FOUND\n");
        return 1;
    }
    flag += sns_search_people(global, id2, &aim2);
    if (flag) {
        printf("404 NOT FOUND\n");
        return 1;
    }
    flag = people_friend(aim1, aim2);
    if (flag) {
        printf("Illeagal add!\n");
        return 1;
    }
    return 0;
}

int add_following() {
    int flag, id1, id2;
    People *aim1, *aim2;
    printf("please tell me the user1 id: ");
    fflush(stdin);
    fscanf(stdin, "%d", &id1);
    printf("please tell me the user2 id: ");
    fflush(stdin);
    fscanf(stdin, "%d", &id2);
    flag = sns_search_people(global, id1, &aim1);
    if (flag) {
        printf("404 NOT FOUND\n");
        return 1;
    }
    flag += sns_search_people(global, id2, &aim2);
    if (flag) {
        printf("404 NOT FOUND\n");
        return 1;
    }
    flag = people_follow(aim1, aim2);
    if (flag) {
        printf("Illeagal add!\n");
        return 1;
    }
    return 0;

}

int del_friend() {
    int flag, id1, id2;
    People *aim1, *aim2;
    printf("please tell me the user1 id: ");
    fflush(stdin);
    fscanf(stdin, "%d", &id1);
    printf("please tell me the user2 id: ");
    fflush(stdin);
    fscanf(stdin, "%d", &id2);
    flag = sns_search_people(global, id1, &aim1);
    if (flag) {
        printf("404 NOT FOUND\n");
        return 1;
    }
    flag += sns_search_people(global, id2, &aim2);
    if (flag) {
        printf("404 NOT FOUND\n");
        return 1;
    }

    flag = people_unfriend(aim1, aim2);
    if (flag) {
        printf("Illeagal add!\n");
        return 1;
    }
    return 0;

}

int del_following() {
    int flag, id1, id2;
    People *aim1, *aim2;
    printf("please tell me the user1 id: ");
    fflush(stdin);
    fscanf(stdin, "%d", &id1);
    printf("please tell me the user2 id: ");
    fflush(stdin);
    fscanf(stdin, "%d", &id2);
    flag = sns_search_people(global, id1, &aim1);
    if (flag) {
        printf("404 NOT FOUND\n");
        return 1;
    }
    flag += sns_search_people(global, id2, &aim2);
    if (flag) {
        printf("404 NOT FOUND\n");
        return 1;
    }

    flag = people_unfollow(aim1, aim2);
    if (flag) {
        printf("Illeagal add!\n");
        return 1;
    }
    return 0;

}

int common_followers() {
    int flag, id1, id2;
    People *aim1, *aim2;
    Circle *result;
    void *callback;
    char temp[1000];
    printf("please tell me the user1 id: ");
    fflush(stdin);
    fscanf(stdin, "%d", &id1);
    printf("please tell me the user2 id: ");
    fflush(stdin);
    fscanf(stdin, "%d", &id2);
    flag = sns_search_people(global, id1, &aim1);
    if (flag) {
        printf("404 NOT FOUND\n");
        return 1;
    }
    flag += sns_search_people(global, id2, &aim2);
    if (flag) {
        printf("404 NOT FOUND\n");
        return 1;
    }
    flag = people_common_followers(aim1, aim2, &result);
    if (flag) {
        printf("Failed!\n");
        return 1;
    }
    callback = get_all_name;
    strcpy(temp, " ");
    circle_map_people(result, temp, callback);
    printf("followings:%s\n", temp);
    return 0;

}

int common_followings() {
    int flag, id1, id2;
    People *aim1, *aim2;
    Circle *result;
    void *callback;
    char temp[1000];
    printf("please tell me the user1 id: ");
    fflush(stdin);
    fscanf(stdin, "%d", &id1);
    printf("please tell me the user2 id: ");
    fflush(stdin);
    fscanf(stdin, "%d", &id2);
    flag = sns_search_people(global, id1, &aim1);
    if (flag) {
        printf("404 NOT FOUND\n");
        return 1;
    }
    flag += sns_search_people(global, id2, &aim2);
    if (flag) {
        printf("404 NOT FOUND\n");
        return 1;
    }
    flag = people_common_followings(aim1, aim2, &result);
    if (flag) {
        printf("Failed!\n");
        return 1;
    }
    callback = get_all_name;
    strcpy(temp, " ");
    circle_map_people(result, temp, callback);
    printf("common_followings:%s\n", temp);
    return 0;
}

int extend_friends() {
    int flag, id;
    People *aim;
    Circle *result;
    void *callback;
    char temp[1000];
    printf("please tell me the id you want : ");
    fflush(stdin);
    fscanf(stdin, "%d", &id);
    flag = sns_search_people(global, id, &aim);
    if (flag) {
        printf("404 NOT FOUND\n");
        return 1;
    } else {
        flag = people_extend_friends(aim, &result);
        callback = get_all_name;
        strcpy(temp, " ");
        circle_map_people(result, temp, callback);
        printf("followings:%s\n", temp);
    }
    return flag;
}

int delete(void *aim) {
    free(aim);
    return 0;
}

int get_all_name(People *data, char *name) {
    char temp[1000] = {""};
    strcat(name, " ");
    strcat(name, data->name);
    itoa(data->id, temp, 10);
    strcat(name, "(");
    strcat(name, temp);
    strcat(name, ")");
    return 0;
}

char *itoa(int num, char *str, int radix) {
    char index[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    unsigned unum;
    int i = 0, j, k;

    if (radix == 10 && num < 0)
    {
        unum = (unsigned) -num;
        str[i++] = '-';
    }
    else unum = (unsigned) num;
    do {
        str[i++] = index[unum % (unsigned) radix];
        unum /= radix;
    } while (unum);
    str[i] = '\0';

    if (str[0] == '-')k = 1;
    else k = 0;
    char temp;
    for (j = k; j <= (i - 1) / 2; j++) {
        temp = str[j];
        str[j] = str[i - 1 + k - j];
        str[i - 1 + k - j] = temp;
    }
    return str;
}