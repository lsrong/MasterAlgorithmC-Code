#include <stdlib.h>

#include "list.h"
#include "set.h"
#include "cover.h"


/**
 * @brief 集合覆盖算法，给定一个待覆盖的集合S, 集合P是集合S的子集S1到Sn，集合C是集合P的最少能覆盖S的所有成员的子集。
 * 贪心算法的思路：每次都尝试尽可能的覆盖members中的更多成员，如果subsets被移除则它的成员也从members移除，
 * 当subsets剩下没有任何集合能够覆盖members的成员时，此时覆盖集合covering就完成了  
 * 
 * @param members 待覆盖的集合S
 * @param Subsets 集合P中的子集
 * @param covering 返回的覆盖集C
 * @return int 0-找到一个完全覆盖集合解，1-不可能实现完全覆盖，-1-其他情况
 */
int cover(Set *members, Set *subsets, Set *covering)
{
   
    Set intersection;  // subset 和 members的交集
    KSet *subset;
    void *data;
    int maxSize;
    ListElem *member, *maxMember;



    // 初始化覆盖结合covering
    // set_init();


    // 循环遍历members和subsets成员，指到其中一个集合被处理完
    
    while(set_size(members) > 0 && set_size(subsets) >  0){
        // 每次循环求的subsets和members成员之间的最大交集的子集subset
        maxSize = 0;
        for(member = list_head(subsets); member != NULL; member = list_next(member))
        {
            if (set_intersection(&intersection, ((KSet *)(list_data(member)))->set, members) != 0)
            {
                return -1;
            }

            if(set_size(&intersection) > maxSize){
                maxMember = member;
                maxSize = set_size(&intersection);
            }

            set_destroy(&intersection);
        }

        // 如果没有找到则说明没有完全覆盖的集合解
        if(maxSize == 0){
            return 1;
        }

        // 找到有则加入到covering
        subset = (KSet *)list_data(maxMember);
        if(set_insert(covering, subset) != 0){
            return -1;
        }

        // 移除被覆盖的members成员和subsets子集
        for(member = list_head(((KSet *)list_data(maxMember))->set); member != NULL; member = list_next(member))
        {
            data = list_data(member);
            if(set_remove(members, (void **) &data) == 0 && members->destroy != NULL){
                members->destroy(data);
            }
        }

        if(set_remove(subsets, (void **) &subset) != 0){
            return -1;
        }
    }

    // members如果有成员存在说明是不可能完全被覆盖。
    if(set_size(members) > 0){
        return -1;
    }

    return 0;
}