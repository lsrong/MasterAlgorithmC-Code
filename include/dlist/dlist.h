#ifndef DLIST_H
#define DLIST_H

#include <stdlib.h>

/**
 * @brief 双向链表结点结构
 */
typedef struct DListElem_
{
    void *data;
    struct DListElem_ *prev;
    struct DListElem_ *next;
} DListElem;

/**
 * @brief 双向链表数据结构
 */
typedef struct DList_
{
    int size;
    int (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);
    DListElem *head;
    DListElem *tail;
}DList;

/**
 * @brief 初始化指定的双向链表。
 * 
 * @param list 双向链表
 * @param destroy 析构函数
 */
void dlist_init(DList *list, void (*destroy)(void *data));

/**
 * @brief 销毁一个双向链表
 * 
 * @param list 链表
 */
void dlist_destroy(DList *list);

/**
 * @brief 将元素插入到指定的双向链表的element结点后面
 * 
 * @param list 链表
 * @param element 插入结点
 * @param data 待插入元素
 * @return int 0-成功，-1-失败
 */
int dlist_insert_next(DList *list, DListElem *element, const void *data);


/**
 * @brief 将元素插到指定的双向链表的element结点前面
 * 
 * @param list 链表
 * @param element 插入结点
 * @param data 待插入元素
 * @return int 0-成功，-1-失败
 */
int dlist_insert_prev(DList *list, DListElem *element, const void *data);


/**
 * @brief 从指定的双向链表中移除element指定的元素，调用方负责管理data所引用的存储空间
 * 
 * @param list 链表
 * @param element 需要移除的结点
 * @param data 数据元素
 * @return int 0-成功，-1-失败
 */
int dlist_remove(DList *list, DListElem *element, void **data);


/**
 * @brief 指定的双向链表的结点数量
 */
#define dlist_size(list)((list)->size)

/**
 * @brief 指定的双向链表的头部结点
 */
#define dlist_head(list)((list)->head)

/**
 * @brief 指定的双向链表的尾部结点
 */
#define dlist_tail(list)((list)->tail)

/**
 * @brief 判定指定结点是否为链表的头部结点
 */
#define dlist_is_head(element)((element)->prev == NULL ? 1:0)

/**
 * @brief 判定指定结点是否为链表的尾部结点
 */
#define dlist_is_tail(element)((element)->next == NULL ? 1:0)

/**
 * @brief 链表结点的数据域
 */
#define dlist_data(element)((element)->data)
/**
 * @brief 链表结点的下一个结点
 */
#define dlist_next(element)((element)->next)

/**
 * @brief 链表结点的上一个节点
 */
#define dlist_prev(element)((element)->prev)

#endif // DLIST_H