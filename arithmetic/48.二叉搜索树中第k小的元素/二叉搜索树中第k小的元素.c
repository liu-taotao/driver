/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/**
 * @brief 这个是二叉树的先序遍历，通过先序遍历得到整个二叉树的所有节点的值后进行排序
 * 
 * @param root 
 * @param values 
 * @param index 
 */
void tree(struct TreeNode *root, int *values, int *index)
{
    if (root == NULL) {
        return;
    }

    values[(*index)++] = root->val;
    tree(root->left, values, index);
    tree(root->right, values, index);
}
/**
 * @brief 这个是排序qsort()的回调函数
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int cmp(int *a, int *b) 
{
    return *(int *)a - *(int *)b;
}
/**
 * @brief 相当于我通过tree()去调用下一层的数据将他们传到这一层，然后进行排序
 * 
 * @param root 
 * @param k 
 * @return int 
 */
int kthSmallest(struct TreeNode* root, int k){
    int *v = calloc(10000, sizeof(int));
    int len = 0;
    tree(root, v, &len);//参数都是指针，但是我可以得到这个常数取指传进去
    qsort(v, len, sizeof(int), cmp);
    return v[k-1];
}