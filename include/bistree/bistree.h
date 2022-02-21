//
// Created by lsrong on 2022/2/21.
//

#ifndef bistree_H
#define bistree_H
#include "bitree.h"

//AVL平衡树的平衡因子
#define AVL_LEFT_HEAVY  1
#define AVL_BALANCED    0
#define AVL_RIGHT_HEAVY -1

#define AVL_SHOW    0
#define AVL_HIDDEN  1

// AVL平衡树结点
typedef struct AvlNode_
{
    void *data;
    int hidden;
    int factor;
} AvlNode;

// 搜索二叉树数据结构，from BiTree
typedef BiTree BisTree;

// bistree_init 初始化二叉搜索树， compare指定的比较函数， destroy指定的析构函数
void bistree_init(BisTree *tree, int(*compare)(const void *key1, const void *key2), void(*destroy)(void *data));

// bistree_destroy 销毁二叉搜索树
void bistree_destroy(BisTree *tree);

// bistree_insert 将一个结点插入二叉树中, 插入后需要调整平衡因子，使得二叉搜索树始终达到平衡。
int bistree_insert(BisTree *tree, const void *data);

// bistree_remove 将一个结点从二叉树中移除，采用惰性移除，并不是真正移除，而是标记hide属性为1。
int bistree_remove(BisTree *tree, const void *data);

// bistree_lookup 从二叉树中查找某个结点.
int bistree_lookup(BisTree *tree, void **data);

// bistree_size 返回二叉树搜索树的结点个数
#define bistree_size(tree)((tree)->size);
#endif //bistree_H
