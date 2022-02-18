#ifndef TRAVERSE_H
#define TRAVERSE_H
#include "bitree.h"
#include "list/list.h"

// preorder  前序方式遍历表达式树
int preorder(const BiTreeNode *node, List *list);


// inorder 中序方式遍历表达式树
int inorder(const BiTreeNode *node, List *list);

// postorder 后序方式遍历表达式树
int postorder(const BiTreeNode *node, List *list);

#endif //TRAVERSE_H
