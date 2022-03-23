#include <stdlib.h>
#include "frames/frames.h"

/**
 * @brief 从空闲帧链表分配一个空闲页帧号
 * 
 * @param frames 空闲帧链表
 * @return int 页帧号， -1-返回失败
 */
int alloc_frame(List *frames)
{
    int frame_number, *data;

    // 如果链表为空则没有分配的页帧号
    if(list_size(frames) == 0){
        return -1;
    }
    
    // 分配相当于从空闲链表中删除，取出一个空闲页帧号
    if(list_remove_next(frames, NULL, (const void **) &data) != 0){
        return -1;
    }

    // 取出的数据赋给frame_number
    frame_number = *data;
    free(data); // 释放data

    return frame_number;
}

/**
 * @brief 将一个页帧号并将其放回到空闲页帧链表中
 * 
 * @param frames 帧链表
 * @param frame_number 需要释放的页帧号
 * @return int 0-成功，-1-失败
 */
int free_frame(List *frames, int frame_number)
{
    int *data;  // 整数指针
    
    // 分配存储空间
    if ((data = (int *)malloc(sizeof(int))) == NULL){
        return -1;
    }

    // 将页帧数放回到空闲帧链表
    *data = frame_number;
    if(list_insert_next(frames, NULL, data) != 0){
        return -1;
    }
    
    return 0;
}