//
// Created by lsrong on 2022/2/21.
//

#ifndef MASTERINGALGORITHM_C_HEAP_H
#define MASTERINGALGORITHM_C_HEAP_H
typedef struct Heap_
{
    int size;
    int (*compare)(const void *data1, const void *data2);
    void (*destroy)(void *data);
    void **tree;
}Heap;

// heap_init 初始化堆
void heap_init(Heap *heap, int (*compare)(const void *data1, const void *data2), void (*destroy)(void *data));

// heap_destroy 删除堆
void heap_destroy(Heap *heap);

// heap_insert 向堆中插入一个结点, 重新分配存储空间以容纳新结点，调整树结构进行重新排列。
int heap_insert(Heap *heap, const void *data);

// heap_extract 释放堆顶部的结点，对剩余结点进行重新排列。
int heap_extract(Heap *heap, void **data);

// heap_size 返回堆容量
#define heap_size(heap)((heap)->size)

#endif //MASTERINGALGORITHM_C_HEAP_H