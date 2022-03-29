#ifndef EVENT_H
#define EVENT_H
#include "queue.h"

typedef struct Event
{
    int type;
    /* other data */
}Event;

/**
 * @brief 事件入队
 * 
 * @param events 事件队列
 * @param event 事件
 * @return int 0-成功，-1-失败
 */
int receive_event(Queue *events, const Event *event);


/**
 * @brief 处理队列中的事件。
 * 
 * @param events 事件队列
 * @param dispatch 事件初始函数
 * @return int 0-成功，-1-成功
 */
int process_event(Queue *events, int(*dispatch)(Event *event));

#endif