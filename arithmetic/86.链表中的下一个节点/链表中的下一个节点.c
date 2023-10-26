/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

/**
 * @brief 标志入栈后 修改
 * 
 * @param head 
 * @param returnSize 
 * @return int* 
 */
int* nextLargerNodes(struct ListNode* head, int* returnSize){
    if (head == NULL) {
        return NULL;
    }
    int *v = (int *)calloc(10241, sizeof(int));
    struct ListNode *ans = head;
    int i = 0, max = 0, top = -1;
    while (ans) {
        v[i++] = ans->val;
        ans = ans->next;
    }
    int *stack = (int *)calloc(i, sizeof(int));
    *returnSize = i--;

    //链表不是空
    while (i > -1) {
        if (top == -1) {
            stack[++top] = v[i];
            v[i--] = 0;
        } else {
            while (top > -1 && stack[top] <= v[i]) {
                --top;
            }
            if (top == -1) {
                stack[++top] = v[i];
                v[i--] = 0;
            } else {
                stack[top+1] = v[i];
                v[i--] = stack[top++];
            }
        }
    }

    return v;
}
