/* traverse.c */
#include "list.h"
#include "traverse.h"

// preorder 前序遍历
int preorder(const BiTreeNode *node, List *list)
{
    // 前序方式遍历表达式树
    if(!bitree_is_eob(node)){
        // 根结点
        if(list_insert_next(list, list_tail(list), bitree_data(node)) != 0)
            return -1;

        if(!bitree_is_eob(bitree_left(node))){
            // 左结点
            if (preorder(bitree_left(node), list) != 0)
                return -1;

            // 右结点
            if(!bitree_is_eob(bitree_right(node))){
                if (preorder(bitree_right(node), list) != 0)
                    return -1;
            }
        }
    }

    return 0;
}

// inorder 中序遍历
int inorder(const BiTreeNode *node, List *list)
{
    // 中序遍历表达式树.
    if(!bitree_is_eob(node)){
        // 左结点
        if(!bitree_is_eob(bitree_left(node))){
            if (inorder(bitree_left(node), list) != 0)
                return -1;
        }

        // 根结点
        if(list_insert_next(list, list_tail(list), bitree_data(node)) != 0)
            return -1;

        // 右结点
        if(!bitree_is_eob(bitree_right(node))){
            if(inorder(bitree_right(node), list) != 0)
                return -1;
        }
    }

    return 0;
}

// postorder 后序遍历
int postorder(const BiTreeNode *node,List *list)
{
    // 后序遍历表达式二叉树
    if (!bitree_is_eob(node)){
        // 左结点
        if(!bitree_is_eob(bitree_left(node))){
            if(postorder(bitree_left(bitree_left(node)), list) != 0){
                return -1;
            }
        }

        // 右结点
        if(!bitree_is_eob(bitree_right(node))){
            if(postorder(bitree_right(node), list) != 0){
                return -1;
            }
        }

        // 根结点
        if (list_insert_next(list, list_tail(list), bitree_data(node)) != 0){
            return -1;
        }
    }

    return 0;
}


