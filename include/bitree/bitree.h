#ifndef BITREE_H
#define BITREE_H
#include <stdlib.h>

/* BiTreeNode 定义二叉树中结点的结构体 */
typedef struct BiTreeNode_
{
    void *data;
    struct BiTreeNode_ *left;
    struct BiTreeNode_ *right;
}BiTreeNode;

/* BiTree 定义二叉树数据结构 */
typedef struct BiTree_
{
    int size
    int (*compare)(const void *key1, const void *key2);
    void (*destroy)(void *data);
    BiTreeNode *root
}BiTree

/* 定义公开接口 */
// bitree_init 初始化一个二叉树数据结构, size默认为0，destroy为成员的析构函数.
void bitree_init(BiTree *tree,void (*destroy)(void *data));

// bitree_destroy 销毁一个二叉树，将树中所有的结点都销毁.
void bitree_destroy(BiTree *tree);
int bitree_





#endif