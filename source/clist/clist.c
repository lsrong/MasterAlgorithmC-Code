#include "clist/clist.h"

#include <stdlib.h>
#include <string.h>

/**
 * @brief 初始化循环链表
 * 
 * @param list 
 * @param destroy 
 */
void clist_init(CList *list, void (*destroy)(void *data))
{
    list->size = 0;
    list->head = NULL;
    list->destroy = destroy;
    list->match = NULL;
}

/**
 * @brief 销毁一个循环链表
 * 
 * @param list 
 */
void clist_destroy(CList *list)
{
    void *data;
    // 遍历所有元素
    while(clist_size(list) > 0)
    {
        // 头部开始移除结点
        if(clist_remove_next(list, list->head, (void **) &data) == 0 && list->destroy != NULL)
        {
            list->destroy(data);
        }
    }
    
    memset(list, 0, sizeof(CList));
}

int clist_insert_next(CList *list, CListElmt *element, const void *data)
{
    CListElmt * newElement;
    // 新结点分配内存空间
    if((newElement = (CListElmt *)malloc(sizeof(CListElmt))) == NULL){
        return -1;
    }
    // 插入元数据
    newElement->data = (void *)data;
    
    if(clist_size(list) == 0)
    {
        // 链表为空，则为插入第一个结点.
        list->head = newElement;
        newElement->next = list->head;
    }
    else
    {
        // 不为空的时候，可以从任意位置插入结点

        newElement->next = element->next;
        element->next = newElement;
    }
    // 自增
    list->size++;
    return 0;
}

int clist_remove_next(CList *list, CListElmt *element, void **data)
{
    CListElmt *oldElement;

    // 链表为空无需操作删除结点
    if(clist_size(list) == 0){
        return -1;
    }

    // 将结点元数据赋值到外部指针.
    *data = element->next->data;

    if(element->next == element)
    {
        // 下一个结点为自身，说明链表只有一个结点,需要将头部结点设置为NULL
        oldElement = element->next;
        list->head = NULL;
    }
    else
    {
        oldElement = element->next;
        element->next = element->next->next;
        
        // 如果移除的是头部结点，则要重置链表的头部结点
        if(oldElement == clist_head(list)){
            list->head = oldElement->next;
        }
    }
    //释放结点空间
    free(oldElement);

    // 自减
    list->size--;

    return 0;
}