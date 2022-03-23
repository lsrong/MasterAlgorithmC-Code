#ifndef FRAMES_H
#define FRAMES_H
#include "list/list.h"

/* FRAMES_H: 虚拟内存的系统页帧管理采用链表的来维护可供分配（空闲）的页帧。 */

/**
 * @brief 从空闲页帧链表中获取空闲页帧号。链表删除操作O(1)
 * 
 * @param frames 帧链表
 * @return int 页帧号, -1  为返回失败
 */
int alloc_frame(List *frames);



/**
 * @brief 将一个页帧号并将其放回到空闲页帧链表中。链表插入操作O(1)
 * 
 * @param frames 帧链表
 * @param frame_number 页帧号
 * @return int 结果标识：0-成功，-1-失败
 */
int free_frame(List *frames, int frame_number);

#endif     //LIST_H