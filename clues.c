
int		count_visible(int *line, int i, int max, int visible);
void	get_row(int **grid, int row, int *out, int i);
void	get_column(int **grid, int col, int *out, int i);
int		check_row_visibility(int **grid, char *clues, int row, int *line);
int		check_col_visibility(int **grid, char *clues, int col, int *line);

int	count_visible(int *line, int i, int max, int visible)
{
	if (i == 4)
		return (visible);
	if (line[i] > max)
		return (count_visible(line, i + 1, line[i], visible + 1));
	return (count_visible(line, i + 1, max, visible));
}

void	get_row(int **grid, int row, int *out, int i)
{
	if (i == 4)
		return ;
	out[i] = grid[row][i];
	get_row(grid, row, out, i + 1);
}

void	get_column(int **grid, int col, int *out, int i)
{
	if (i == 4)
		return ;
	out[i] = grid[i][col];
	get_column(grid, col, out, i + 1);
}

int	check_row_visibility(int **grid, char *clues, int row, int *line)
{
	int	rev[4];

	if (row == 4)
		return (1);
	get_row(grid, row, line, 0);
	if (count_visible(line, 0, 0, 0) != clues[8 + row] - '0')
		return (0);
	rev[0] = line[3];
	rev[1] = line[2];
	rev[2] = line[1];
	rev[3] = line[0];
	if (count_visible(rev, 0, 0, 0) != clues[12 + row] - '0')
		return (0);
	return (check_row_visibility(grid, clues, row + 1, line));
}

int	check_col_visibility(int **grid, char *clues, int col, int *line)
{
	int	rev[4];

	if (col == 4)
		return (1);
	get_column(grid, col, line, 0);
	if (count_visible(line, 0, 0, 0) != clues[col] - '0')
		return (0);
	rev[0] = line[3];
	rev[1] = line[2];
	rev[2] = line[1];
	rev[3] = line[0];
	if (count_visible(rev, 0, 0, 0) != clues[4 + col] - '0')
		return (0);
	return (check_col_visibility(grid, clues, col + 1, line));
}
