//
// Created by lsrong on 2022/2/21.
//
#include <stdlib.h>
#include <string.h>

#include "heap/heap.h"

/* 定义数组下标转换成二叉树的位置关系 */
// 父结点
#define heap_parent(npos) (int)(((npos) - 1) / 2)

// 左子结点
#define heap_left(npos)(((npos) * 2) + 1)

// 右子结点
#define heap_right(npos)(((npos) * 2) + 2)

// heap_init 初始化堆
void heap_init(Heap *heap, int(*compare)(const void *key1, const void *key2), void (*destroy)(void *data))
{
    heap->size = 0;
    heap->compare = compare;
    heap->destroy = destroy;
    heap->tree = NULL;
}

void heap_destroy(Heap *heap)
{
    int i;
    if(heap->destroy != NULL){
        for(i = 0; i< heap_size(heap); i++){
            heap->destroy(heap->tree[i]);
        }
    }

    // 释放堆空间
    free(heap->tree);
    memset(heap, 0, sizeof(Heap));
}

int heap_insert(Heap *heap, const void *data)
{
    // ipos 当前位置， ppos 父结点位置
    void *temp;
    int ipos, ppos;

    // 重新分配存储空间，temp为tree新增的结点。
    if((temp = (void **) realloc(heap->tree, (heap_size(heap) +1) * sizeof(void *))) == NULL){
        return -1;
    }else{
        heap->tree = temp;
    }

    // 从结点树的最后一个位置插入新结点
    heap->tree[heap_size(heap)] =(void *) data;

    ipos = heap_size(heap);
    ppos = heap_parent(ipos);

    //
    while(ipos > 0 && heap->compare(heap->tree[ppos], heap->tree[ipos]) < 0){
        temp = heap->tree[ppos];
        heap->tree[ppos] = heap->tree[ipos];
        heap->tree[ipos] = temp;

        ipos = ppos;
        ppos = heap_parent(ipos);
    }

    heap->size++;

    return 0;
}