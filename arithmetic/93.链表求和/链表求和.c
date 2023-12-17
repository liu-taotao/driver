/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

/**
 * @brief 实际上也就是判断是否有进位了, 因为全部都是逆序的, 所以不必很担心是否会漏掉一部分, 甚至都不用判断这两个链表是否为空。
 * 
 * @param l1 
 * @param l2 
 * @return struct ListNode* 
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    struct ListNode *res = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode *ans = res;
    int tem = 0;
    res->val = -1;
    res->next = NULL;
    while (l1 && l2) {
        res->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        tem = l1->val + l2->val + tem;
        res->next->val = tem % 10;
        tem /= 10;
        res = res->next;
        res->next = NULL;
        l1 = l1->next;
        l2 = l2->next;
    }
    if (l1) {
        while (l1) {
            res->next = (struct ListNode*)malloc(sizeof(struct ListNode));
            tem = l1->val + tem;
            res->next->val = tem % 10;
            tem /= 10;
            res = res->next;
            res->next = NULL;
            l1 = l1->next; 
        }
    } else {
        while (l2) {
            res->next = (struct ListNode*)malloc(sizeof(struct ListNode));
            tem = l2->val + tem;
            res->next->val = tem % 10;
            tem /= 10;
            res = res->next;
            res->next = NULL;
            l2 = l2->next; 
        }
    }
    if (tem) {
        res->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        res->next->val = tem % 10;
        tem /= 10;
        res = res->next;
        res->next = NULL;
    }
    return ans->next;
}