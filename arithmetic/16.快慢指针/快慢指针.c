
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


/**
 * @brief 这里用到了快慢指针，如果链表有环，就证明可以使fast追到slow指针。
 * 
 * @param head 
 * @return true 
 * @return false 
 */
bool hasCycle(struct ListNode *head) {
    struct ListNode *slow = NULL, *fast = NULL;
    if (head == NULL || head->next == NULL) {
        return false;
    }
    slow = head;
    fast = head->next->next;
    while (slow != fast) {
        if (fast == NULL || fast->next == NULL) {
            return false;
        }
        slow = slow->next;
        fast = fast->next->next;
    }
    return true;
}