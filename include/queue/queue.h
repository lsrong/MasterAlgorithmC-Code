#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

/**
 * @brief 队列数据结构，使用链表来实现
 */
typedef List Queue;

/**
 * @brief 初始化队列，和链表初始化一样
 */
#define queue_init list_init

/**
 * @brief 销毁队列，和链表销毁过程一样
 */
#define queue_destroy list_destroy

/**
 * @brief 入队操作
 * 
 * @param queue 队列
 * @param data 元数据
 * @return int 0-成功，-1-失败
 */
int queue_enqueque(Queue *queue, const void *data);

/**
 * @brief 出队操作
 * 
 * @param queue 队列
 * @param data 需要移除的数据
 * @return int 0-成功，-1-失败
 */
int queue_dequeue(Queue *queue, void **data);

/**
 * @brief 返回队列的头部元素
 */
#define queue_peek(queue)((queue)->head == NULL ? NULL : (queue)->head->data)

/**
 * @brief 返回队列的个数
 */
#define queue_size list_size

#endif