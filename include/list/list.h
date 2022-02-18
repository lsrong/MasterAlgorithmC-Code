#ifndef LIST_H
#define LIST_H

// ListElem 链表结构中的元素.
typedef struct ListElem_ {
    void *data;
    struct ListElem_ *next;
} ListElem;

// List 链表数据结构.
typedef struct List_ {
    int size;
    int (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);
    ListElem *head;
    ListElem *tail;
} List;

int list_insert_next(List *list, ListElem *elem, const void *data);


#define list_tail(list) ((list)->tail)

#endif     //LIST_H