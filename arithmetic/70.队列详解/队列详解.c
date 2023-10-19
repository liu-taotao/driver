/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/**
 * @brief 这里使用到了队列，也就是有值就在队列的最后入队，取值就从队列的前面出队，注意数据的类型。
 * 
 * @param root 
 * @param returnSize 
 * @return int* 
 */
int* decorateRecord(struct TreeNode* root, int* returnSize) {
    int *v = calloc(1100, sizeof(int));
    int front = -1, rear = -1, i = 0;

    struct TreeNode *queue[1100];//队列
    struct TreeNode *p;//工作指针，取值用

    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }

    queue[++rear] = root;
    while (front < rear) {
        p = queue[++front];//出队
        v[i++] = p->val;

        //当前节点左边是否有节点
        if (p->left) {//有 入队
            queue[++rear] = p->left;
        }
        //当前节点右边是否有节点
        if (p->right) {//有 入队
            queue[++rear] = p->right;
        }
    }
    *returnSize = i;
    return v;
}