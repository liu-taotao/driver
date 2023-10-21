/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

/**
 * @brief Get the Intersection Node object 也就是同时遍历很多遍 直到两个链表相交
 * 
 * @param headA 
 * @param headB 
 * @return struct ListNode* 
 */
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    if (headA == NULL || headB == NULL) {
        return NULL;
    }

    struct ListNode *res = headA;
    struct ListNode *ans = headB;

    while (res != ans) {
        res = res == NULL ? headB : res->next;
        ans = ans == NULL ? headA : ans->next;
    }
    return ans;
}
