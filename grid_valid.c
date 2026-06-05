
int	is_grid_valid(int **grid, char *clues);
int	check_row_visibility(int **grid, char *clues, int row, int *line);
int	check_col_visibility(int **grid, char *clues, int col, int *line);

int	is_grid_valid(int **grid, char *clues)
{
	int	line[4];

	if (!check_row_visibility(grid, clues, 0, line))
		return (0);
	if (!check_col_visibility(grid, clues, 0, line))
		return (0);
	return (1);
}
