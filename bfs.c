#include "lem_in.h"

int	count_size_map(char **connection_matrix)
{
	int	i;

	i = 0;
	while (connection_matrix[i])
		i++;
	return (i);
}

int	find_start_row(char **connection_matrix)
{
	int	j;

	j = 0;
	while (connection_matrix[j][j] != START)
		j++;
	return (j);
}
	
void	print_adjacent_rooms(char **connection_matrix, int current)
{
	int	i;

	i = 0;
	while (connection_matrix[current][i] != 0)
	{
		if (connection_matrix[current][i] == CONNECTED)
			ft_printf("\t...room %d.\n", i);
		i++;
	}
	return ;
}

int	*store_following_rooms(char **connection_matrix, int current, int *ignore)
{
	int	*adjacent_rooms;
	int	j;
	int	i;

	i = 0;
	j = 0;
	adjacent_rooms = ft_memalloc(count_size_map(connection_matrix) * sizeof(int) + 1);
	while (connection_matrix[current][i] != 0)
	{
		if (connection_matrix[current][i] == CONNECTED)
		{
			adjacent_rooms[j] = ignore[i] ? 0 : i;
			j++;
		}
		i++;
	}
	return (adjacent_rooms);
}
