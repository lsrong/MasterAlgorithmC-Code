#include <stdlib.h>
#include <string.h>

#include "event.h"
#include "queue.h"

/**
 * @brief 将事件加入队列中，enqueue
 * 
 * @param events 事件队列
 * @param event 事件
 * @return int 0-成功， -1-异常情况
 */
int receive_event(Queue *events, const Event *event)
{
    // 新事件
    Event *newEvent;

    // 分配事件内存空间
    if((newEvent = (Event *)malloc(sizeof(Event))) == NULL){
        return -1;
    }
    // 复制事件进行入队
    memcpy(newEvent, event, sizeof(Event));

    if(queue_enqueque(events, newEvent) != 0){
        return -1;
    }
    
    return 0;
}

/**
 * @brief 处理队列中的事件，dequeue => dispatch
 * 
 * @param events 事件队列
 * @param dispatch 处理函数
 * @return int 0-成功，-1-异常情况
 */
int process_event(Queue *events, int (*dispatch)(Event *event))
{
    Event *event;
    
    // 如果事件队列为空则不用处理
    if(queue_size(events) == 0){
        return -1;
    }

    // 从事件队列中移出一个事件来执行
    if(queue_dequeue(events, (void **)&event) != 0){
        return -1;
    }

    // 处理事件 
    dispatch(event);
    // 释放空间
    free(event);

    return 0;
}