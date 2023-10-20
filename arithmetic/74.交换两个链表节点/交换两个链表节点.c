/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

/**
 * @brief 请看题解
 * 
 * @param head 
 * @return struct ListNode* 
 */
struct ListNode* swapPairs(struct ListNode* head){
    struct ListNode *dump = (struct ListNode*)malloc(sizeof(struct ListNode));
    dump->val = -1;
    dump->next = head;
    struct ListNode* res = dump;

    while (res->next != NULL && res->next->next != NULL) {
        struct ListNode *nod1 = res->next;
        struct ListNode *nod2 = res->next->next;

        res->next = nod2;
        nod1->next = nod2->next;

        nod2->next = nod1;
        res = nod1;
    }
    return dump->next;
}