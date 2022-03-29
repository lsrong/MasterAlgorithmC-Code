#ifndef STACK_H
#define STACK_H
#include <stdlib.h>
#include "list/list.h"

/**
 * @brief 栈的检索方式：后进先出（LIFO），示例用链表来时先栈的数据结构，插入和删除的复杂度都为O(1)
 */
typedef List Stack;

/**
 * @brief 栈初始化和链表初始化的过程相同
 */
#define stack_init list_init

/**
 * @brief 栈销毁函数和链表销毁的过程相同
 */
#define stack_destroy list_destroy

/**
 * @brief 入栈操作
 * 
 * @param stack 栈
 * @param data 元数据
 * @return int 0-成功，-1-失败
 */
int stack_push(Stack *stack,  const void *data);

/**
 * @brief 出栈操作
 * 
 * @param stack 栈
 * @param data 元数据
 * @return int 0-成功，-1-失败
 */
int stack_pop(Stack *stack, void **data);

/**
 * @brief 返回栈顶的结点
 */
#define stack_peek(stack)((stack)->head == NULL  ? NULL : ((stack)->head->data))

/**
 * @brief 栈的结点个数
 */
#define stack_size list_size

#endif