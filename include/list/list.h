#ifndef LIST_H
#define LIST_H

// ListElem 链表结构中的元素： data-数据成员, next-下一个元素指针
typedef struct ListElem_ {
    void *data;
    struct ListElem_ *next;
} ListElem;

// List 链表数据结构：size-成员个数，destroy-析构函数， head-头部结点，tail-尾部结点
typedef struct List_ {
    int size;
    int (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);
    ListElem *head;
    ListElem *tail
} List;

// list_init 初始化链表操作，size设置为0，head,tail设置为NULL.
void list_init(List *list, void (*destroy)(void *data));

// list_destroy 销毁由list指定的链表,复杂度 O(n)
void list_destroy(List *list);

// list_insert_next 从指定元素中插入一个元素.
int list_insert_next(List *list, ListElem *elem, const void *data);

// list_remove_next 从指定元素后删除一个元素
int list_remove_next(List *list, ListElem *element, const void **data);

// list_size 链表中的个数
#define list_size(list) ((list)->size)

// list_head 链表的头部元素
#define list_head(list)((list)->head)

// list_tail 链表的尾部元素
#define list_tail(list) ((list)->tail)

// list_is_head 元素是否为链表的头部结点
#define list_is_head(list, element)((element) == (list)->head ? 1 :0)

// list_is_tail 元素是否为链表的尾部结点
#define list_is_tail(list, element)((element)->next == NULL ? 1: 0)

// list_data 结点中的数据
#define list_data(element)((element)->data)

// list_next 结点指向的下一个结点
#define list_next(element)((element)->next)
#endif     //LIST_H