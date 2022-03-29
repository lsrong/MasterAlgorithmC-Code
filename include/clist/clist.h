#ifndef CLIST_H
#define CLIST_H
#include <stdlib.h>

// CListElmt 循环链表结点结构体
typedef struct CListElmt_
{
    void *data;
    struct CListElmt_ *next;
} CListElmt;

// CList 循环链表结构体
typedef struct CList_
{
    int size;
    int (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);
    CListElmt *head;
}CList;


/**
 * @brief 初始化循环链表
 * 
 * @param list 循环链表
 * @param destroy 元数据析构函数
 */
void clist_init(CList *list, void (*destroy)(void *data));

/**
 * @brief 销毁指定的循环链表
 * 
 * @param list 循环链表
 */
void clist_destroy(CList *list);

/**
 * @brief 在循环链表指定结点的下一个位置插入新元数据结点，由调用方维护data的存储空间。
 * 
 * @param list 循环链表
 * @param element 指定结点
 * @param data 新结点的元数据
 * @return int 0-成功，-1-失败
 */
int clist_insert_next(CList *list, CListElmt *element, const void *data);

/**
 * @brief 删除循环链表指定结点的下一个结点，由调用方负责管理data的存储空间
 * 
 * @param list 循环链表
 * @param element 指定结点
 * @param data 元数据指针
 * @return int 0-成功，-1-失败
 */
int clist_remove_next(CList *list, CListElmt *element, void **data);

/**
 * @brief 返回循环链表的结点数目
 */
#define clist_size(list)((list)->size)

/**
 * @brief 返回循环链表的头部结点
 */
#define clist_head(list)((list)->head)

/**
 * @brief 返回链表结点元素的元数据，data
 */
#define clist_data(element)((element)->data)

/**
 * @brief 返回循环链表结点的下一个指向结点指针
 */
#define clist_next(element)((element)->next)

#endif