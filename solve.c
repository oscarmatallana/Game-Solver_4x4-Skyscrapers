
int	try_value(int **grid, char *clues, int row, int col);
int	is_valid(int **grid, int row, int col, int val);
int	next_cell(int **grid, char *clues, int row, int col);
int	solve_grid(int **grid, char *clues, int row, int col);
int	is_grid_valid(int **grid, char *clues);

int	solve_grid(int **grid, char *clues, int row, int col)
{
	if (row == 4)
		return (is_grid_valid(grid, clues));
	if (grid[row][col] != 0)
		return (next_cell(grid, clues, row, col));
	return (try_value(grid, clues, row, col));
}

int	next_cell(int **grid, char *clues, int row, int col)
{
	if (col == 3)
		return (solve_grid(grid, clues, row + 1, 0));
	return (solve_grid(grid, clues, row, col + 1));
}

/*int	try_value(int **grid, char *clues, int row, int col, int val)
{
	if (val > 4)
		return (0);
	if (is_valid(grid, row, col, val))
	{
		grid[row][col] = val;
		if (next_cell(grid, clues, row, col))
			return (1);
		grid[row][col] = 0;
	}
	return (try_value(grid, clues, row, col, val + 1));
}*/

int	try_value(int **grid, char *clues, int row, int col)
{
	int	val;

	val = 1;
	while (val <= 4)
	{
		if (is_valid(grid, row, col, val))
		{
			grid[row][col] = val;
			if (next_cell(grid, clues, row, col))
				return (1);
			grid[row][col] = 0;
		}
		val++;
	}
	return (0);
}
