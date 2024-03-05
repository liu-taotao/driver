/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

/**
 * @brief 这是一个很重要的思想，就是相当于使用两个链表节点，分别保存下一个节点和当前这个不为val的节点，一直更新，直到找完整个链表。
 * 
 * @param head 
 * @param val 
 * @return struct ListNode* 
 */
struct ListNode* removeElements(struct ListNode* head, int val) {
    struct ListNode *ans = NULL;
    struct ListNode *res = NULL;
    //找到第一个不为val的节点
    while (head != NULL && head->val == val) {
        head = head->next;
    }
    if (head == NULL) {
        return NULL;
    }
    ans = head->next;//指向可能被删除的节点
    res = head;//指向当前节点, 这个节点的意思是相当于中间件，一直保存上一个节点不为val的节点
    while (ans) {
        if (ans->val == val) {
            res->next = ans->next;
        } else {
            res = ans;
        }
        ans = ans->next;
    }
    return head;
}