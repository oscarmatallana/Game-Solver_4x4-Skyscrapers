
int	check_row(int **g, int r, int c, int val);
int	check_col(int **g, int c, int r, int val);

int	is_valid(int **g, int r, int c, int val)
{
	return (!check_row(g, r, 0, val) && !check_col(g, c, 0, val));
}

int	check_row(int **g, int r, int c, int val)
{
	if (c == 4)
		return (0);
	if (g[r][c] == val)
		return (1);
	return (check_row(g, r, c + 1, val));
}

int	check_col(int **g, int c, int r, int val)
{
	if (r == 4)
		return (0);
	if (g[r][c] == val)
		return (1);
	return (check_col(g, c, r + 1, val));
}
