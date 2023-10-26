/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

/**
 * @brief 相当于 把下一个节点保存 然后把下一个节点复制到当前节点 再把下一个节点释放
 * 
 * @param node 
 */
void deleteNode(struct ListNode* node) {
    struct ListNode *res = node->next;
    memcpy(node, node->next, sizeof(struct ListNode));
    free(res);
    res = NULL;
}