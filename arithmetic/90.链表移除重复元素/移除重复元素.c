/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

/**
 * @brief 基本思想就是 得到这个节点 然后再从这个节点往后 遍历 删除重复的元素 依次往后
 * 
 * @param head 
 * @return struct ListNode* 
 */
struct ListNode* removeDuplicateNodes(struct ListNode* head){
    struct ListNode *ans = head;
    while (ans != NULL) {
        struct ListNode *res = ans;
        while (res->next != NULL) {
            if (ans->val == res->next->val) {
                res->next = res->next->next;
            } else {
                res = res->next;
            }
        }
        ans = ans->next;
    }
    return head;
}
