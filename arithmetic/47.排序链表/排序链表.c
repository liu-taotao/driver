/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
int cmp(int *a, int *b)
{
    return *(int*)a - *(int*)b;
}
/**
 * @brief 先取出原链表中的值，在进行排序后，存储到一个新申请的链表，注意保护号这个新链表的头节点
 * 
 * @param head 
 * @return struct ListNode* 
 */
struct ListNode* sortList(struct ListNode* head){
    int *v = calloc(50000, sizeof(int));
    int n = 0;
    if (head == NULL || head->next == NULL) {
        return head;
    }
    while (head != NULL) {
        v[n++] = head->val;
        head = head->next;
    }
    qsort(v, n, sizeof(int), cmp);
    struct ListNode *ans = malloc(sizeof(struct ListNode));
    struct ListNode *res = ans;
    for (int i = 0; i < n; i++) {
        ans->next = malloc(sizeof(struct ListNode));
        ans->next->val = v[i];
        ans = ans->next;
        ans->next = NULL;
    }
    return res->next;

}