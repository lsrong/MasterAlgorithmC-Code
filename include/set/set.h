#ifndef SET_H
#define SET_H

#include "list.h"

/**
 * @brief 采用链表来实现集合，链表数据结构需要一定的运行时开销，适合小型到中等模型的集合数据
 *  集合的定义：相关联成员的无序组合，且每个成员在集合中只出现一次（唯一，不重复）
 */
typedef List Set;

/**
 * @brief 初始化参数一个Set数据结构，match-匹配函数指针，判断两个成员是否匹配上，key1=key2返回1，否则返回0，destroy-析构函数指针，销毁data成员内存空间。 
 * 
 * @param set 集合数据
 * @param match 匹配函数指针
 * @param destroy 析构函数指针
 */
void set_init(Set *set, int(*match)(const void *key1, const void *key2), void (*destroy)(void *data));

/**
 * @brief 销毁集合，由于是链表实现的，因此用链表的销毁函数，list_destroy
 */
#define set_destroy list_destroy;

/**
 * @brief 将一个数据data，插入到指定的集合中
 * 
 * @param set 集合
 * @param data 元数据
 * @return int 0-成功，1-成员已经在集合中存在，-1-失败
 */
int set_insert(Set *set, const void *data);

/**
 * @brief 从集合中移除数据域同data相同的成员
 * 
 * @param set 集合
 * @param data 数据域
 * @return int 0-成功，-1-失败
 */
int set_remove(Set *set, void **data);

/**
 * @brief 求两个集合的并集
 * 
 * @param setu 合并之后的集合
 * @param set1 集合1
 * @param set2 集合2
 * @return int 0-成功，-1-失败
 */
int set_union(Set *setu, const Set *set1, const Set *set2);

/**
 * @brief 求两个集合的交集
 * 
 * @param seti 相交之后的集合
 * @param set1 集合1
 * @param set2 集合2
 * @return int 0-成功，-1-失败
 */
int set_intersection(Set *seti, const Set *set1, const Set *set2);

/**
 * @brief 求两个集合的差集
 * 
 * @param setd 集合1和集合2的差集
 * @param set1 集合1
 * @param set2 集合2
 * @return int 0-成功，-1-失败
 */
int set_difference(Set *setd, const Set *set1, const Set *set2);

/**
 * @brief 断言一个数据域是否存在于指定的集合中
 * 
 * @param set 集合
 * @param data 数据域
 * @return int 1-找到成员，-1-未找到
 */
int set_is_member(Set *set, void *data);

/**
 * @brief 断言集合1是否是集合2的子集
 * 
 * @param set1 集合1
 * @param set2 集合2
 * @return int set1是set2的子集返回1，否则返回-1
 */
int set_is_subset(Set *set1, Set *set2);

/**
 * @brief 断言集合1是否和集合2相等
 * 
 * @param set1 集合1
 * @param set2 集合2
 * @return int set1等于set2返回1，否则返回-1
 */
int set_is_equal(Set *set1, Set *set2);

/**
 * @brief 返回集合中的成员个数
 */
#define set_size(set)((set)->size)
#endif