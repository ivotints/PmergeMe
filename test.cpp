int Jacobsthal(int n)
{
	if (n == 0 || n == 1)
		return n;

	return Jacobsthal(n - 1) + 2 * Jacobsthal(n - 2);
}

//0 1 1 3 5 11 21 43 85 171 341 683 1365 2731 5461 10923 21845 43691
int Jacobsthal(int n)
{
	int dp[n + 1];

	dp[0] = 0;
	dp[1] = 1;

	for (int i = 2; i <= n; i++)
		dp[i] = dp[i - 1] + 2 * dp[i - 2];

	return dp[n];
}
