

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

/**
 * @brief 这个是指向头节点的链表，这个很重要的，因为，这个可以重头开始读取存储的数据，不需要指针在一次指向头节点
 * 
 * @param l1 
 * @param l2 
 * @return struct ListNode* 
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    struct ListNode *head = NULL, *tail = NULL;
    int sum = 0, flag = 0, n1 = 0, n2 = 0;
    if (l1 == NULL) {
        return l2;
    }
    if (l2 == NULL) {
        return l1;
    }
    while (l1 != NULL || l2 != NULL) {
        n1 = l1 != NULL ? l1->val : 0;
        n2 = l2 != NULL ? l2->val : 0;
        sum = n1 + n2 + flag;
        if (head == NULL) {
            head = tail = malloc(sizeof(struct ListNode));
            tail->val = sum % 10;
            flag = sum / 10;
            tail->next = NULL;
        } else {
            tail->next = malloc(sizeof(struct ListNode));
            tail->next->val = sum % 10;
            flag = sum /10;
            tail = tail->next;
            tail->next = NULL;
        }
        if (l1) {
            l1 = l1->next;
        }
        if (l2) {
            l2 = l2->next;
        }
    }
    if (flag) {
        tail->next = malloc(sizeof(struct ListNode));
        tail->next->val = flag;
        tail->next->next = NULL;
    }
    return head;
}