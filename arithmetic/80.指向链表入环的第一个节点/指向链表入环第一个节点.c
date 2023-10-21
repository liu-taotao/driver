/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

/**
 * @brief 重点是算 快慢指针相遇后 再申请一个指针 与慢指针跑 最后指向第一个相遇的节点
 * 
 * @param head 
 * @return struct ListNode* 
 */
struct ListNode *detectCycle(struct ListNode *head) {
    struct ListNode *fast = head, *slow = head;
    if (head == NULL) {
        return head;
    }
    while (fast != NULL) {
        slow = slow->next;
        
        if (fast->next == NULL) {
            return NULL;
        }
        fast = fast->next->next;
        //重新定义一个指向指向链表头部；
        //随后，它和 slow\textit{slow}slow 每次向后移动一个位置。
        //最终，它们会在入环点相遇
        if (fast == slow) {
            struct ListNode *ptr = head;
            while (ptr != slow) {
                slow = slow->next;
                ptr = ptr->next;
            }
            return ptr;
        }
    }
    return NULL;
}