/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/**
 * @brief 这里用到了递归这种方式，就是为了能够在一直往下
 *          还用一个重点就是为什么每次递归都是从root开始呢，这里我猜想是和链表一样的都是指向下一个比如 head = head->next;
 * 
 * @param root 
 * @return int 
 */
int maxDepth(struct TreeNode* root){
    if (root == NULL) {
        return 0;
    }
    int leftdeep = maxDepth(root->left) + 1;
    int rightdeep = maxDepth(root->right) + 1;
    if (leftdeep < rightdeep) {
        return rightdeep;
    } else {
        return leftdeep;
    }
}