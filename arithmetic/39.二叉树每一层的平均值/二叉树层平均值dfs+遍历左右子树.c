/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

/**
 * @brief 深度优先搜索，遍历每一层求和，并算出每一层有多少个节点
 * 
 * @param root 
 * @param sum 
 * @param count 
 * @param level 
 */
void dfs(struct TreeNode *root, double *sum, int *count, int level)
{
    if (root == NULL) {
        return;
    }
    sum[level] += root->val;
    count[level]++;
    dfs(root->left, sum, count, level + 1);
    dfs(root->right, sum, count, level + 1);
}

/**
 * @brief  calloc()申请空间， dfs深度优先搜索求和，最后求平均值，
 *         (*returnSize)是相当于可以一个工程，可以在上一层使用这个变量获取下一层的值
 * 
 * @param root 
 * @param returnSize 
 * @return double* 
 */
double* averageOfLevels(struct TreeNode* root, int* returnSize){
    int *count = calloc(1001, sizeof(int));
    double *sum = calloc(1001, sizeof(double));
    double *res = calloc(1001, sizeof(double));

    dfs(root, sum, count, 0);
    *returnSize = 0;
    for (int i = 0; count[i] != 0; i++) {
        res[i] = sum[i] / count[i];
        (*returnSize) ++;
    }
    free(count);
    free(sum);
    return res;
}