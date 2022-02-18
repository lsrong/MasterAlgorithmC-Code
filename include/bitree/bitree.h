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
    int size;
    int (*compare)(const void *key1, const void *key2);
    void (*destroy)(void *data);
    BiTreeNode *root;
}BiTree;

/* 定义公开接口 */
// bitree_init 初始化一个二叉树数据结构, size默认为0，destroy为成员的析构函数.
void bitree_init(BiTree *tree,void (*destroy)(void *data));

// bitree_destroy 销毁一个二叉树，将树中所有的结点都销毁.
void bitree_destroy(BiTree *tree);

// bitree_insert_left 将结点插入到二叉树中，待插入结点将作为参数指定的结点的左子结点.
int bitree_insert_left(BiTree *tree, BiTreeNode *node, const void *data);

// bitree_insert_right 将结点插入到二叉树中，待插入结点将作为参数指定结点的右子结点.
int bitree_insert_right(BiTree *tree, BiTreeNode *node, const void *data);

// bitree_remove_left 将指定结点的左子结点移除，移除顺序按照后序遍历从参数node的左子结点开始依次移除.
void bitree_remove_left(BiTree *tree, BiTreeNode *node);

// bitree_remove_right 将指定结点的右边子结点移除，操作和bitree_remove_left相似.
void bitree_remove_right(BiTree *tree, BiTreeNode *node);

// bitree_merge 合并两个字二叉树，以 data 作为根结点，合并后的左右子结点分别设置为left 和 right.
int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const void *data);


// 宏定义，用于访问BiTree,BitTreeNode中的成员接口
// bitree_size 结点数
#define bitree_size(tree) ((tree)->size)

// bitree_root 根结点
#define bitree_root(tree) ((tree)->root)

// bitree_is_eob 节点是否为树结束点（NULL）
#define bitree_is_eob(node) ((node) == NULL)

// bitree_is_leaf 是否为叶子结点
#define bitree_is_leaf(node) ((node)->left == NULL && (node)->right == NULL)


// bitree_data 返回结点的数据
#define bitree_data(node) ((node)->data)

// bitree_left 返回左子节点
#define bitree_left(node) ((node)->left)

// bitree_right 返回右子结点
#define bitree_right(node) ((node)->right)
#endif // BITREE_H