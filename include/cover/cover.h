#ifndef COVER_H
#define COVER_H

#include "set.h";


/**
 * @brief 定义成员元素的子集结构，用key标识， 集合P
 */
typedef struct KSet_
{
    void *key;
    Set *set;
}KSet;


/**
 * @brief 集合覆盖算法，给定一个待覆盖的集合S, 集合P是集合S的子集S1到Sn，集合C是集合P的最少能覆盖S的所有成员的子集。
 * 
 * @param members 待覆盖的集合S
 * @param Subsets 集合P中的子集
 * @param covering 返回的覆盖集C
 * @return int 0-找到一个完全覆盖集合解，1-不可能实现完全覆盖，-1-其他情况（异常情况）
 */
int cover(Set *members, Set *subsets, Set *covering);
#endif