#ifndef PAGE_H
#define PAGE_H

#include "clist/clist.h"


typedef struct Page_
{
    int number;
    int reference;
}Page;

/**
 * @brief 第二次机会页面置换算法
 * 
 * @param current 当前循环链表页面结点
 * @return int 待置换的页面帧数
 */
int replace_page(CListElmt **current);

#endif