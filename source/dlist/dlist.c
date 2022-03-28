#include <stdlib.h>
#include "dlist/dlist.h"



/**
 * @brief 初始化一个双向链表
 * 
 * @param list 双向链表
 * @param destroy 析构函数
 */
void dlist_init(DList *list, void (*destroy) (void *data))
{
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
}

/**
 * @brief 销毁指定的双向链表
 * 
 * @param list 要删除的链表
 */
void dlist_destroy(DList *list)
{
    void *data;

    // 当链表不为空的时候才可能有删除操作
    while(dlist_size(list) > 0){
        // 移除链表元素，如果存在有数据析构函数则调用析构函数
        if(dlist_remove(list, dlist_tail(list), (void **) &data) ==0
         && list->destroy != NULL)
        {
            list->destroy(data);
        }
    }
}

/**
 * @brief 在链表的指定结点的下一个位置插入新结点
 * 
 * @param list 链表
 * @param element 指定结点位置 
 * @param data 新结点的元数据
 * @return int 0-成功，-1-失败
 */
int dlist_insert_next(DList *list, DListElem *element,const void *data)
{
    DListElem *newElement;
    // 只有在链表为空的情况下才允许 elemenet 为NULL.
    if (element == NULL && dlist_size(list) != 0){
        return -1;
    }
    
    // 赋值元数据
    newElement->data = (void *) data;

    if(dlist_size(list) == 0)
    {
        // 原链表为空，插入第一个结点。
        list->head = newElement;
        list->head->prev = NULL;
        list->head->next = NULL;
        list->tail = newElement;
    }
    else
    {
        // 链表不为空的情况，在指定结点的下一个位置插入新结点。
        newElement->next = element->next;
        newElement->prev = element;
        if(element->next == NULL){
            list->tail = newElement;
        }else{
            element->next->prev = newElement;
        }
        element->next = newElement;
    }
    
    // 自增结点数
    list->size++;
    return 0;
}

/**
 * @brief 在链表的指定位置的前一个位置插入新结点
 * 
 * @param list 链表
 * @param element 指定结点位置
 * @param data 待插入的元数据
 * @return int 0-成功， -1-失败 
 */
int list_insert_prev(DList *list, DListElem *element, const void *data)
{
    // 声明新结点
    DListElem *newElement;

    // 链表不为空时，element不能为NULL
    if(element == NULL && list_size(list)!= 0){
        return -1;
    }

    newElement->data = (void *)data;
    
    // 在链表指定位置的前面插入新结点
    if(element == NULL)
    {
        // 链表为空时新结点设置为头部结点
        list->head = newElement;
        list->head->next = NULL;
        list->head->prev = NULL;
        list->tail = newElement;
    }
    else
    {
        // 链表不为空时，插入到指定结点的前一个位置
        newElement->next = element;
        newElement->prev = element->prev;
        if(element->prev == NULL){
            list->head = newElement;
        }else{
            element->prev->next = newElement;
        }
        element->prev = newElement;
    }

    // 自增结点数
    list->size++;
    return 0;
}

int dlist_remove(DList *list, DListElem *element, void **data)
{
    // 指定结点为空或者链表为空时，不允许执行删除操作.
    if(element == NULL ||  dlist_size(list) == 0){
        return -1;
    }
    // 将元数据赋值到外部指针。
    *data = element->data;

    // 判断是否删除头部或者其他结点
    if(element == list->head)
    {
        // 删除头部结点
        list->head = element->next;
        if(list->head == NULL)
        {
            list->tail = NULL;
        }else
        {
            element->next->prev = NULL;
        }
    }
    else
    {
        // 删除其他位置的结点。
        element->prev->next = element->next;
        if(element->next == NULL)
        {
            list->tail = element->prev;
        }
        else
        {
            element->next->prev = element->prev;
        }
    }

    // 释放结点存储空间
    free(element);
    
    // 自减少
    list->size--;

    return 0;
}

