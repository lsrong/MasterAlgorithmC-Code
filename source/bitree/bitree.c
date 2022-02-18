#include <string.h>
#include <stdlib.h>

#include "bitree.h"

// bitree_init 初始化二叉树
void bitree_init(BiTree *tree, void (*destroy)(void *data))
{
    tree->size = 0;
    tree->destroy = destroy;
    tree->root= NULL;
}

// bitree_destroy 销毁二叉树
void bitree_destroy(BiTree *tree)
{
    // 清除树中的所有结点
    bitree_remove_left(tree, NULL);

    // 清空二叉树内存空间
    memset(tree, 0, sizeof(BiTree));
}

// bitree_insert_left 向二叉树中的指定操作结点上插入新结点
int bitree_insert_left(BiTree *tree, BiTreeNode *node, const void *data)
{
    BiTreeNode *newNode, **position;
    // 需要确定插入的位置结点
    if(node == NULL){
        // 当且仅当空树时才允许从根节点插入
        if(bitree_size(tree) > 0){
            return -1;
        }
        position = &tree->root;
    }else{
        // 当node的左子结点不为空时才允许插入
        if(bitree_left(node) != NULL){
            return -1;
        }
        position = &node->left;
    }

    // 新结点分配空间
    if((newNode = (BiTreeNode *) malloc(sizeof(BiTreeNode))) == NULL)
        return -1;

    // 新结点插入到树中
    newNode->data= (void *)data;
    newNode->left = NULL;
    newNode->right = NULL;
    *position = newNode;

    // 树的已插入结点数量
    tree->size++;

    return 0;
}

// bitree_insert_right 向二叉树中的指定操作结点上插入新的右子结点.
int bitree_insert_right(BiTree *tree, BiTreeNode *node, const void *data)
{
    BiTreeNode *newNode, **position;

    // 判断插入位置
    if(node == NULL){
        // 当树不为空的时候才允许从根结点插入, data
        if(bitree_size(tree) > 0){
            return -1;
        }
        position = &tree->root;
    }else{
        // 当操作结点的右子结点为空的时候才允许插入, data
        if (bitree_right(node) != NULL){
            return -1;
        }
        position = &node->right;
    }

    // 新结点分配内存空间
    if ((newNode = (BiTreeNode *) malloc(sizeof(BiTreeNode))) == NULL)
        return -1;

    // 插入结点到指定位置
    newNode->data = &data;
    newNode->left = NULL;
    newNode->right = NULL;
    *position = newNode;

    // 树结点数自增
    tree->size++;

    return 0;
}

// bitree_remove_left  移除以指定结点的左子结点的为根的子树.
void bitree_remove_left(BiTree *tree, BiTreeNode *node)
{
    BiTreeNode  **position;
    // 空树的时候不允许操作
    if(bitree_size(tree) == 0)
        return;

    // 确定删除结点的位置
    if(node == NULL)
        position = &tree->root;
    else
        position = &node->left;

    // 删除以此位置为树的所有结点，后序遍历的方式（递归）
    if (position != NULL){
        bitree_remove_left(tree, *position);
        bitree_remove_right(tree, *position);

        if(tree->destroy != NULL){
            // 调用数据的析构函数
            tree->destroy(bitree_data(*position));
        }
        // 释放空间
        free(*position);
        *position = NULL;

        // 减少树的结点数
        tree->size--;
    }

    return;
}

//bitree_remoce_right 移除指定结点的右子结点为根的所有结点.
void bitree_remove_right(BiTree *tree, BiTreeNode *node)
{
    BiTreeNode **position;

    // 当树为空时不操作删除
    if(bitree_size(tree) == 0)
        return;

    // 判断需要删除的结点位置
    if(node == NULL)
        position = &tree->root;
    else
        position = &node->right;

    // 清空当前结点以及所有子结点
    if (*position != NULL){
        // 后序遍历删除子结点
        bitree_remove_right(tree, *position);
        bitree_remove_left(tree, *position);

        if (tree->destroy != NULL){
            // 调用析构函数
            tree->destroy(bitree_data(*position));
        }
        // 释放空间
        free(*position);
        *position = NULL;

        // 自减结点数
        tree->size--;
    }

    return;
}

// bitree_merge 合并两个二叉树，data作为合并后的根.
int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const void *data)
{
    // 初始化合并后的树结构
    bitree_init(merge, left->destroy);

    // 将data作为合并后的根结点
    if(bitree_insert_left(merge, NULL, data) != 0){
        bitree_destroy(merge);
        return  -1;
    }

    // 左树的根为合并根的左子结点，右树的根为合并根的右子结点，
    bitree_root(merge)->left = bitree_root(left);
    bitree_root(merge)->right = bitree_root(right);

    // 统计所有的树结点数量
    merge->size = merge->size + bitree_size(left) + bitree_size(right);

    // 左树和右树与合并后的树断开结点联系.
    left->root = NULL;
    left->size = 0;
    right->root = NULL;
    right->size = 0;

    return 0;
}
