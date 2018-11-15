#include "lem_in.h"

int		get_start_id(char **matrix)
{
	int		i;

	i = 0;
	while (matrix[i][i] != START)
		i++;
	return (i);
}

int		get_end_id(char **matrix)
{
	int		i;

	i = 0;
	while (matrix[i][i] != END)
		i++;
	return (i);
}
