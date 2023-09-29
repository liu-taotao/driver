/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

/**
 * @brief 在一个区间内翻转数组，并且想滑动窗口一样，没过一次就流向下一个窗口
 * 
 * @param head 
 * @param left 
 * @param right 
 * @return struct ListNode* 
 */
struct ListNode *reverseBetween(struct ListNode *head, int left, int right) {
    // 因为头节点有可能发生变化，使用虚拟头节点可以避免复杂的分类讨论
    struct ListNode *dummyNode = malloc(sizeof(struct ListNode));
    dummyNode->val = -1;
    dummyNode->next = head;

    struct ListNode *pre = dummyNode;
    for (int i = 0; i < left - 1; i++) {
        pre = pre->next;
    }
    struct ListNode *cur = pre->next;
    struct ListNode *next;
    //测试
    struct ListNode *v = head;
    while (v) {
        printf("%d ", v->val);
        v = v->next;
    }
    printf("\n");

    for (int i = 0; i < right - left; i++) {
        next = cur->next;
        cur->next = next->next;
        next->next = pre->next;
        pre->next = next;
        //测试
        struct ListNode *v = head;
        while (v) {
            printf("%d ", v->val);
            v = v->next;
        }
        printf("\n");

    }
    return dummyNode->next;
}

