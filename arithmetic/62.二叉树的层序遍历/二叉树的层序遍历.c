/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/**
 * @brief 二叉树的层序遍历
 * 
 * @param root 
 * @param returnSize 
 * @param returnColumnSizes 
 * @return int** 
 */
int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes){
    int **ans = (int **)malloc(sizeof(int*)*2000);
    *returnSize = 0;
    if (root == NULL) {
        return NULL;
    }
    int columnSizes[2000];
    struct TreeNode *queue[2000];
    int rear = 0, head = 0;
    queue[rear++] = root;

    while (rear != head) {
        ans[(*returnSize)] = (int *)malloc(sizeof(int) * (rear - head));
        columnSizes[(*returnSize)] = rear - head;
        int start = head;
        head = rear;

        for (int i = start; i < head; i++) {
            ans[(*returnSize)][i - start] = queue[i]->val;
            if (queue[i]->left) {
                queue[rear++] = queue[i]->left;
            }
            if (queue[i]->right) {
                queue[rear++] = queue[i]->right;
            }
        }
        (*returnSize)++;
    }
    *returnColumnSizes = (int *)malloc(sizeof(int) * (*returnSize));
    for (int i = 0; i < *returnSize; i++) {
        (*returnColumnSizes)[i] = columnSizes[i];
    }
    return ans;
}