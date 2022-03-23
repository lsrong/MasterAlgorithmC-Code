//
// Created by lsrong on 2022/3/10.
//
#include <stdlib.h>
#include <string.h>
#include "list/list.h"

// list_init 初始化链表
void list_init(List *list, void (*destroy)(void *data))
{
    // 初始化链表操作
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
}

// list_destroy 销毁整个链表数据结构
void list_destroy(List *list)
{
    void *data;

    // 循环遍历结点并执行销毁函数
    while(list_size(list) > 0){
        // 调用移除链表元素方法
        if(list_remove_next(list, NULL, (const void **) &data) == 0
        && list->destroy != NULL){
            list->destroy(data);
        }
    }

    //
    memset(list, 0, sizeof(List));
}

// list_insert_next 向链表中插入一个新结点，element为null时插入链表头部，不为null时为其他结点
int list_insert_next(List *list, ListElem *element, const void *data)
{
    ListElem *newElement;

    // 分配内存空间给新结点
    if((newElement = (ListElem *) malloc(sizeof(ListElem))) == NULL){
        return -1;
    }
    // 将数据添加到新结点
    newElement->data = (void *)data;
    if(element == NULL){
        // 从头部插入新结点, head作为新结点的next指针
        if(list_size(list) == 0){
            list->tail = newElement;
        }
        newElement->next = list->head;
        list->head = newElement;
    }else{
        // 从其他元素后插入
        if(element->next == NULL){
            // 末尾结点时，需要更新tail
            list->tail = newElement;
        }
        newElement->next = element;
        element->next = newElement;
    }

    list->size++;

    return 0;
}

// list_remove_next 在指定元素后面移除结点，需要考虑链表尾部边界问题，
int list_remove_next(List *list, ListElem *element, const void **data)
{
    ListElem *oldElement;
    // 为空时不需要处理
    if(list_size(list) == 0){
        return -1;
    }
    if(element == NULL) {
        // 从头部开始删除结点
        *data = list->head->data;
        oldElement = list->head;
        list->head = list->head->next;
        if (list_size(list) == 1){
            list->tail = NULL;
        }
    }else{
        // 末尾结点不支持移除（无下一个结点）
        if(element->next == NULL){
            return -1;
        }
        oldElement = element->next;
        element->next = element->next->next;
        if(element->next == NULL){
            // 更新尾部结点
            list->tail = element;
        }
    }

    free(oldElement);
    list->size --;

    return 0;
}


