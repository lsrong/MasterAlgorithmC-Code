#include <stdlib.h>

#include "list.h"
#include "set.h"

/**
 * @brief 初始化集合
 * 
 * @param set 
 * @param match 
 * @param destroy 
 */
void set_init(Set *set, int (*match)(const void *key1, const void *key2), void (*destroy)(void *data))
{
    list_init(set, destroy);
    set->match = match;
}

/**
 * @brief 数据是否在集合中
 * 
 * @param set 结合
 * @param data 数据
 * @return int 1-在集合中，-1-不在集合中
 */
int set_is_memner(Set *set, void *data)
{
    ListElem *member;
    // 循环链表元素对比匹配数据域是否相同，相同返回1，否则返回-1
    for(member = list_head(set); member != NULL; member = list_next(member))
    {
        // 调用匹配初始化定义的比较函数
        if(set->match(member->data, data)){
            return 1;
        }

    }
    return -1;
}


/**
 * @brief 插入一个数据域到集合中
 * 
 * @param set 集合
 * @param data 数据域
 * @return int 1-数据已存在于集合中，0-插入成功，-1-失败情况
 */
int set_insert(Set *set,const void *data)
{
    if (set_is_member(set, data)){
        return 1;
    }

    return list_insert_next(set, list_tail(set), data);
}

/**
 * @brief 在集合中移除和data相同的成员，因此需要匹配成员并执行移除操作（list_remove_next）
 * 
 * @param set 集合
 * @param data 数据域
 * @return int 0-成功，-1-失败
 */
int set_remove(Set *set, void **data)
{
    ListElem *member, *prev;
    // 记录链表遍历的前一个结点，用于链表删除
    prev = NULL;

    // 遍历集合，匹配数据
    for(member = list_head(set);member != NULL; member = list_next(member))
    {
        // 匹配到则退出遍历
        if(set->match(member->data, *data)){
            break;
        }
        prev = member;
    }

    // 没有匹配到数据域
    if(member == NULL){
        return -1;
    }

    // 移除成员
    return list_remove_next(set, prev, data);
}

/**
 * @brief 获得两个集合的并集：初始化setu，第一个集合set1所有元素插入setu， 第二个集合set2元素插入之前判断是否已存在，不存在才插入。
 * 
 * @param setu 最终的交集
 * @param set1 集合1
 * @param set2 集合2
 * @return int 
 */
int set_union(Set *setu,const Set *set1,const Set *set2)
{
    ListElem *member;
    void *data;

    // 初始化setu
    set_init(setu, set1->match, NULL);

    // set1的元素插入到setu
    for(member = list_head(set1); member != NULL; member = list_next(member))
    {
        // 直接使用底层链表操作
        data = list_data(member);
        if (list_insert_next(setu, list_tail(setu), data) == -1)
        {
            set_destroy(setu);
            return -1;
        }
    }

    // set2的元素检查重复性后插入setu
    for(member = list_head(set2); member != NULL; member = list_next(member))
    {
        if(set_is_member(setu, list_data(member))){
            continue;
        }

        data = list_data(member);
        if(list_insert_next(setu, list_tail(setu), data) == -1){
            set_destroy(setu);
            return -1;
        }    
    }

    return 0;
}

/**
 * @brief 获得两个集合的交集 
 * 
 * @param seti 交集
 * @param set1 集合1
 * @param set2 集合2
 * @return int 0-成功， -1-失败
 */
int set_intersection(Set *seti, const Set *set1, const Set *set2)
{
    ListElem *member;
    void *data;

    // 初始化seti变量
    set_init(seti, set1->match, NULL);

    // 遍历set1成员，匹配是否在set2存在，如果存在则就是交集中的成员
    for(member = list_head(set1); member != NULL; member = list_next(member))
    {
        if(set_is_member(set2, list_data(member))){
            data = list_data(member);
            if (list_insert_next(seti, list_tail(seti), data) != 0){
                set_destroy(seti);

                return -1;
            }
        }
    }
    return 0;
}

/**
 * @brief 获得两个集合的差集
 * 
 * @param setd 差集
 * @param set1 集合1
 * @param set2 集合2
 * @return int 0-成功，-1-失败
 */
int set_difference(Set *setd, const Set *set1, const Set *set2)
{
    ListElem *member;
    void *data;

    // 初始化差集
    set_init(setd, set1->match, NULL);

    // 遍历set1的所有元素，如果成员不在集合set2的就是差集的元素。
    for(member = list_head(set1); member != NULL; member = list_next(member))
    {
        if(!set_is_member(set2, list_data(member)))
        {
            data = list_data(member);
            if(list_insert_next(setd, list_tail(setd), data) != 0)
            {
                set_destroy(setd);

                return -1;
            }
        }
    }

    return 0;
}

/**
 * @brief 判断集合1是否是集合2的子集，set2包含set1.
 * 
 * @param set1 集合1
 * @param set2 集合2
 * @return int set1是set2的子集返回1，否则返回-1
 */
int set_is_subset(Set *set1, Set *set2)
{
    // 首先从数量开始判断，set1->size > set2->size,则set1不可能是set2的子集。
    if(list_size(set1) > list_size(set2)){
        return -1;
    }

    ListElem *member;


    // set1所有的元素必须在set2中
    for(member = list_head(set1); member != NULL; member = list_next(member))
    {
        if(!set_is_memner(set2, list_data(member)))
        {
            return -1;
        }
    }

    return 1;
}

/**
 * @brief 判断集合1和集合2是否相同
 * 
 * @param set1 集合1
 * @param set2 集合2
 * @return int set1等于set2返回1，否则返回-1
 */
int set_is_equal(Set *set1, Set *set2)
{
    if(list_size(set1) != list_size(set2)){
        return -1;
    }

    return  set_is_subset(set1, set2);
}