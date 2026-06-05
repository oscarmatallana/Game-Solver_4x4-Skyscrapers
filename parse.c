
int	parse_recursive(char *str, char *clues, int index);

int	parse_input(char *str, char *clues)
{
	if (!str)
		return (0);
	return (parse_recursive(str, clues, 0));
}

int	parse_recursive(char *str, char *clues, int index)
{
	if (*str == '\0')
		return (index == 16);
	if (*str >= '1' && *str <= '4')
	{
		if (index >= 16)
			return (0);
		clues[index] = *str;
		return (parse_recursive(str + 1, clues, index + 1));
	}
	return (parse_recursive(str + 1, clues, index));
}
