#include <stdlib.h>

#include "list.h"
#include "stack.h"

/**
 * @brief 入栈操作，将数据加入到栈结构中，由外部管理data的存储空间
 * 
 * @param stack 栈
 * @param data 元数据
 * @return int 0-成功， -1-失败
 */
int stack_push(Stack *stack, const void *data)
{
    // 入栈，从头部开始插入到链表中。
    return list_insert_next(stack, NULL, data);
}

/**
 * @brief 出栈操作，将数据从栈中取出，由外部管理data的存储空间
 * 
 * @param stack 栈
 * @param data 元素的元数据
 * @return int 0-成功，-1-失败
 */
int stack_pop(Stack *stack, void **data)
{
    // 出栈，从头部开始移除链表结点。
    return list_remove_next(stack, NULL, data);
}