/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

/**
 * @brief 这里相当于形成了一个环，将要旋转最后一个找到作为头节点，
 * 
 * @param head 
 * @param k 
 * @return struct ListNode* 
 */
struct ListNode* rotateRight(struct ListNode* head, int k){
    if (k == 0 || head == NULL || head->next == NULL) {
        return head;
    }
    int n = 1;
    struct ListNode *res = head;
    while (res->next != NULL) {
        res = res->next;
        n++;
    }
    int num = n - k % n; //到这里是要得到不旋转的数
    if (num == n) {
        return head;
    }
    res->next = head;
    while (num--) {
        res = res->next;
    }
    struct ListNode *ans = res->next;//将ans作为头节点，下一个置空。
    res->next = NULL;
    return ans;
}