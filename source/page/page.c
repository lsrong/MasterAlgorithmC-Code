#include "clist/clist.h"
#include "page/page.h"

/**
 * @brief 第二次机会页面置换算法实现，检索Page中存储的reference成员，如为1则重置为0并遍历下一个页面，如果为0，则站到应该被替换的页面。
 * 
 * @param current 
 * @return int 
 */
int replace_page(CListElmt **current)
{
    // 操作系统如果有访问页面就将reference设置为1，说明最近有使用的页面，置换算法第一个会将1重置为0，如果找到为0的说明为空闲的页面，则返回该待置换的页面。
    while(((Page *)((*current)->data))->reference != 0)
    {
        // 将页面的reference重置为0
        ((Page *)(* current)->data)->reference = 0;
        *current = clist_next(*current);
    }
    
    // 待置换的页面(第二次遍历reference=0的页面）
    return ((Page *)(*current)->data)->number;
}