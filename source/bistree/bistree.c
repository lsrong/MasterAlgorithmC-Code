//
// Created by lsrong on 2022/2/21.
//
#include <stdlib.h>
#include <string.h>
#include "bistree/bistree.h"

static void destroy_right(BisTree *tree,BiTreeNode *node);

// todo ** 进一步了解旋转逻辑 **
// rotate_left 左旋操作，包括LL旋转和LR旋转
static void rotate_left(BiTreeNode **node)
{
    BiTreeNode *left, *grandchild;

    left = bitree_left(*node);
    if(((AvlNode *) bitree_data(left))->factor == AVL_LEFT_HEAVY){
        // LL旋转的实现
        bitree_left(*node) = bitree_right(left);
        bitree_right(left) = *node;
        ((AvlNode *) bitree_data(*node))->factor = AVL_BALANCED;
        ((AvlNode *) bitree_data(left))->factor = AVL_BALANCED;
        *node = left;
    }else{
        // LR旋转的实现
        grandchild = bitree_right(left);
        bitree_right(left) = bitree_left(grandchild);
        bitree_left(grandchild) = left;
        bitree_left(*node) = bitree_right(grandchild);
        bitree_right(grandchild) = *node;
        // 调整之后的平衡因子，取决于grandchild结点的原平衡因子.
        switch (((AvlNode *) bitree_data(grandchild))->factor)  {
            case AVL_LEFT_HEAVY:
                ((AvlNode *) bitree_data(*node))->factor = AVL_RIGHT_HEAVY;
                ((AvlNode *) bitree_data(left))->factor = AVL_BALANCED;
                break;
            case AVL_BALANCED:
                ((AvlNode *) bitree_data(*node))->factor = AVL_BALANCED;
                ((AvlNode *) bitree_data(left))->factor = AVL_BALANCED;
                break;
            case AVL_RIGHT_HEAVY:
                ((AvlNode *) bitree_data(*node))->factor = AVL_BALANCED;
                ((AvlNode *) bitree_data(left))->factor = AVL_LEFT_HEAVY;
                break;
        }
        ((AvlNode *) bitree_data(grandchild))->factor = AVL_BALANCED;
        *node = grandchild;
    }
}

// rotate_right 右旋操作
static void rotate_right(BiTreeNode **node)
{
    BiTreeNode  *right, *grandchild;
    right = bitree_right(*node);
    if(((AvlNode *)bitree_data(right))->factor == AVL_RIGHT_HEAVY){
        // 实现RR右右旋转操作
        bitree_right(*node) = bitree_left(right);
        bitree_left(right) = *node;
        ((AvlNode *) bitree_data(*node))->factor = AVL_BALANCED;
        ((AvlNode *) bitree_data(right))->factor = AVL_BALANCED;
        *node = right;
    }else{
        // 实现RL右左旋转操作
        grandchild = bitree_left(right);
        bitree_left(right) = bitree_right(grandchild);
        bitree_right(grandchild) = right;
        bitree_right(*node) = bitree_left(grandchild);
        bitree_left(grandchild) = *node;
        // 旋转过后的情况
        switch (((AvlNode *) bitree_data(grandchild))->factor){
            case AVL_LEFT_HEAVY:
                ((AvlNode *) bitree_data(*node))->factor = AVL_BALANCED;
                ((AvlNode *) bitree_data(right))->factor = AVL_RIGHT_HEAVY;
                break;
            case AVL_BALANCED:
                ((AvlNode *) bitree_data(*node))->factor = AVL_BALANCED;
                ((AvlNode *) bitree_data(right))->factor = AVL_BALANCED;
                break;
            case AVL_RIGHT_HEAVY:
                ((AvlNode *) bitree_data(*node))->factor = AVL_LEFT_HEAVY;
                ((AvlNode *) bitree_data(right))->factor = AVL_BALANCED;
                break;
        }
        ((AvlNode *) bitree_data(grandchild))->factor = AVL_BALANCED;
        *node = grandchild;
    }
}



// destroy_left 从左结点开始递归删除节点
static void destroy_left(BisTree *tree, BiTreeNode *node)
{
    BiTreeNode  **position;

    // 如果树为空则不执行操作
    if(bitree_size(tree) == 0){
        return;
    }

    // 判断删除位置， NULL => 从根结点开始删除
    if (node == NULL){
        position = &tree->root;
    }else{
        position = &node->left;
    }

    // 删除结点
    if(*position != NULL){
        destroy_left(tree, *position);
        destroy_right(tree, *position);
        if(tree->destroy != NULL){
            tree->destroy(((AvlNode *) bitree_data(*position))->data);
        }

        // 释放内存空间
        free((*position)->data);
        free(*position);
        *position = NULL;

        // 自减
        tree->size--;
    }
}

// destroy_right 从右边递归删除结点
static void destroy_right(BisTree *tree, BiTreeNode *node)
{
    BiTreeNode **position;

    // 如果树为空则不操作
    if(bitree_size(tree) == 0){
        return;
    }

    // 判断删除的位置
    if (node == NULL){
        position = &tree->root;
    }else{
        position = &node->right;
    }

    // 执行删除操作
    if (*position != NULL){
        destroy_right(tree, *position);
        destroy_left(tree, *position);

        if(tree->destroy != NULL){
            tree->destroy(((AvlNode *) bitree_data(*position))->data);
        }

        free((*position)->data);
        free(*position);
        *position = NULL;

        tree->size--;
    }
}

// todo insert 插入一个结点到二叉搜索树.
static int insert(BisTree *tree, BiTreeNode **node, const void *data,int *balanced)
{
    AvlNode  *avl_data;
    int cmpval, retval;

    if(bitree_is_eob(node)){
        // 插入到叶子结点上面
        if((avl_data = (AvlNode *) malloc(sizeof (AvlNode))) == NULL){
            return -1;
        }
        avl_data->data = (void *)data;
        avl_data->factor = AVL_BALANCED;
        avl_data->hidden = AVL_SHOW;

        return bitree_insert_left(tree, *node, avl_data);
    }else{
        cmpval = tree->compare(data, ((AvlNode *)bitree_data(*node))->data);
        if(cmpval < 0){
            // < 0 插入到左边
            if(bitree_is_eob(bitree_left(*node))){
                // 左子结点是叶子结点时候，直接插入
                if((avl_data = (AvlNode *) malloc(sizeof(AvlNode))) == NULL){
                    return -1;
                }
                avl_data->factor = AVL_BALANCED;
                avl_data->hidden = AVL_SHOW;
                avl_data->data = (void *)data;
                if(bitree_insert_left(tree, *node, avl_data) != 0){
                    return -1;
                }
                *balanced = 0;
            } else{
                if((retval = insert(tree, &bitree_left(*node), data, balanced)) != 0){
                    return retval;
                }
            }

            if(!(*balanced)){
                switch (((AvlNode *) bitree_data(*node))->factor) {
                    case AVL_LEFT_HEAVY:
                        rotate_left(node);
                        *balanced = 1;
                        break;
                    case AVL_BALANCED:
                        ((AvlNode *) bitree_data(*node))->factor = AVL_LEFT_HEAVY;
                        break;
                    case AVL_RIGHT_HEAVY:
                        ((AvlNode *) bitree_data(*node))->factor = AVL_BALANCED;
                        *balanced = 1;
                        break;
                }
            }
        }else if(cmpval > 0){
            // > 0 插入到右边
            if(bitree_is_eob(*node)){
                if((avl_data = (AvlNode *)malloc(sizeof(AvlNode))) == NULL){
                    return -1;
                }
                avl_data->factor = AVL_BALANCED;
                avl_data->hidden = AVL_SHOW;
                avl_data->data = (void *)data;

                if(bitree_insert_right(tree, *node, avl_data) != 0){
                    return -1;
                }

                *balanced = 0;
            }else{
                if((retval = insert(tree, &bitree_right(*node), data, balanced) != 0)){
                    return retval;
                }
            }

            if(!(*balanced)){
                switch (((AvlNode *) bitree_data(*node))->factor) {
                    case AVL_LEFT_HEAVY:
                        ((AvlNode *) bitree_data(*node))->factor = AVL_BALANCED;
                        *balanced = 1;
                        break;
                    case AVL_BALANCED:
                        ((AvlNode *) bitree_data(*node))->factor = AVL_RIGHT_HEAVY;
                        break;
                    case AVL_RIGHT_HEAVY:
                        rotate_right(node);
                        *balanced = 1;
                        break;
                }
            }

        }else{
            // cmpval = 0,相等的情况
            if(((AvlNode *)bitree_data(*node))->hidden == AVL_SHOW){
                // 如果节点为不隐藏时候不做任何处理
                return 1;
            }else{
                if(tree->destroy != NULL){
                    // 删除之前的保存的data值
                    tree->destroy(((AvlNode *) bitree_data(*node))->data);
                }
                ((AvlNode *) bitree_data(*node))->data = (void *)  data;
                ((AvlNode *) bitree_data(*node))->hidden = AVL_SHOW;

                // 结构没有变化，因此不需要重新设置平衡
                *balanced =1;
            }
        }
    }
    return 0;
}

// hide 惰性删除某个结点
static int hide(BisTree *tree, BiTreeNode *node, const void *data)
{
    int cmpval, retval;

    // 叶子结点不执行操作
    if(bitree_is_eob(node)){
        return -1;
    }

    cmpval = tree->compare(data, ((AvlNode *) bitree_data(node))->data);
    if(cmpval <  0){
        // 左结点
        retval = hide(tree, bitree_left(node), data);
    }else if(cmpval > 0){
        // 右结点
        retval = hide(tree, bitree_right(node), data);
    }else{
        // 标记为隐藏状态
        ((AvlNode *) bitree_data(node))->hidden = AVL_HIDDEN;
        retval = 0;
    }

    return retval;
}

// lookup 在二叉搜索树中检索某个具体的结点
static int lookup(BisTree *tree, BiTreeNode *node, void **data)
{
    int cmpval, retval;
    if(bitree_is_eob(node)){
        // 叶结点， 认为没有找到
        return -1;
    }

    cmpval = tree->compare(*data, ((AvlNode *) bitree_data(node))->data);
    if(cmpval < 0){
        // 位于左边
        retval = lookup(tree, bitree_left(node), data);
    }else if(cmpval > 0){
        // 位于右边
        retval = lookup(tree, bitree_right(node), data);
    }else{
        // 有相同的情况，判断隐藏状态
        if(((AvlNode *) bitree_data(node))->hidden == AVL_SHOW){
            // 找到数据。
            *data = ((AvlNode *)bitree_data(node))->data;
            retval = 0;
        }else{
            // 没有检索到
            retval = -1;
        }
    }

    return retval;
}

// bitstree_init 初始化搜搜二叉树
void bitstree_init(BisTree *tree, int (* compare)(const void *key1, const void *key2), void (*destroy)(void *data))
{
    // 初始化二叉树
    bitree_init(tree, destroy);
    tree->compare = compare;
}

// bistree_destroy 删除一颗二叉树
void bistree_destroy(BisTree *tree)
{
    destroy_left(tree, NULL);

    memset(tree, 0, sizeof(BisTree));
}

// bistree_insert 插入结点
int bistree_insert(BisTree *tree, const void *data)
{
    int balanced = 0;
    return insert(tree, &bitree_root(tree), data, &balanced);
}

// bistree_remove 删除结点
int bistree_remove(BisTree *tree, const void *data)
{
    return hide(tree, bitree_root(tree), data);
}

// bistree_lookup 从二叉树中检索某个数据.
int bistree_lookup(BisTree *tree, void **data)
{
    return lookup(tree, bitree_root(tree), data);
}





