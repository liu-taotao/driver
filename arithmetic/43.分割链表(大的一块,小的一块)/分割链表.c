/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

/**
 * @brief 思想就是: 再创建两个链表，存放一大一小数据，最后连接起来，注意指针指向位置，最后一个没有指向了一定要记得置空
 *                  最后将小的链表尾节点，指向打的头节点。
 * 
 * @param head 
 * @param x 
 * @return struct ListNode* 
 */
struct ListNode* partition(struct ListNode* head, int x){
    struct ListNode *smallhead = malloc(sizeof(struct ListNode));
    struct ListNode *small = smallhead;
    struct ListNode *lasthead = malloc(sizeof(struct ListNode));
    struct ListNode *last = lasthead;
    while (head != NULL) {
        if (head->val < x) {
            small->next = head;
            small = small->next;
        } else {
            last->next = head;
            last = last->next;
        }
        head = head->next;
    }
    last->next = NULL;
    small->next = lasthead->next;
    return smallhead->next;
}