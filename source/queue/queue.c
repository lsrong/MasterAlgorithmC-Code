#include <stdlib.h>

#include "list.h"
#include "queue.h"

/**
 * @brief 入队操作，往队列的尾部插入元素，调用list_insert_next来插入到链表尾部
 * 
 * @param queue 队列
 * @param data 元数据
 * @return int 0-成功，-1-失败
 */
int queue_enqueue(Queue *queue, const void *data)
{
    // 入队
    return list_insert_next(queue, list_tail(queue), data);
}


/**
 * @brief 出队操作，往队列的头部删除元素，调用list_remove_nex来删除链表头部元素
 * 
 * @param queue 链表
 * @param data 移除的数据
 * @return int 0-成功，-1-失败
 */
int quueue_dequeue(Queue *queue, void **data)
{
    // 出队
    return list_remove_next(queue, NULL, data);
}
