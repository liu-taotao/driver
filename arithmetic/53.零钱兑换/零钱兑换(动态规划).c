
/**
 * @brief 这里的零钱兑换，用到了动态规划
 * 
 * @param coins 
 * @param coinsSize 
 * @param amount 
 * @return int 
 */
int coinChange(int* coins, int coinsSize, int amount){
	int *dp = malloc(sizeof(int) * (amount + 1));
	for (int i = 0; i < amount + 1; i++) {
		dp[i] = amount + 1;
	}
	dp[0] = 0;
	for (int i = 1; i <= amount; i++) {
		for (int j = 0; j < coinsSize; j++) {
			if (i >= coins[j]) {
				dp[i] = fmin(dp[i - coins[j]] + 1, dp[i]);
			}
		}
	}
	int ret = dp[amount] > amount ? -1 : dp[amount];
	free(dp);
	return ret;
}