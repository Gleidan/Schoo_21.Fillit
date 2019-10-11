#include "fillit.h"

int		ft_place(t_list *list, char ***map, int x, int y)
{
	int		x_plus;
	int		y_plus;
	int		block;
	char	**tetromino;
	char	**map_ptr;

	map_ptr = *map;
	block = 0;
	y_plus = -1;
	tetromino = ((t_tetris *)(list->content))->table;
	while (tetromino[++y_plus])
	{
		x_plus = -1;
		while (tetromino[y_plus][++x_plus])
		{
			if (!(map_ptr[y + y_plus]))
				return (0);
			if (map_ptr[y + y_plus][x + x_plus] == '.' && tetromino[y_plus][x_plus] != '.')
			{
				map_ptr[y + y_plus][x + x_plus] = ((t_tetris * )(list->content))->letter;
				block++;
			}
		}
	}
	return (block == 4);
}

void	ft_remove(t_list *list, char ***map)
{
	int		x;
	int		y;
	int		count;
	char	**map_ptr;

	y = 0;
	count = 0;
	map_ptr = *map;
	while (map_ptr[y])
	{
		x = 0;
		while (map_ptr[y][x])
		{
			if (count == 4)
				return ;
			if (map_ptr[y][x] == ((t_tetris *)(list->content))->letter && ++count)
				map_ptr[y][x] = '.';
			x++;
		}
		y++;
	}
}

int		ft_check_place(t_list *list, char ***map, int x, int y)
{
	int		x_plus;
	int		y_plus;
	int		block;
	char	**tetromino;
	char	**map_ptr;

	map_ptr = *map;
	block = 0;
	y_plus = -1;
	tetromino = ((t_tetris *)(list->content))->table;
	while (tetromino[++y_plus])
	{
		x_plus = -1;
		while (tetromino[y_plus][++x_plus])
		{
			if (!(map_ptr[y + y_plus]))
				return (0);
			if (map_ptr[y + y_plus][x + x_plus] == '.' && tetromino[y_plus][x_plus] != '.')
				block++;
		}
	}
	return (block == 4);
}

int		ft_backtracking_solver(t_list *list, char ***map)
{
	int		x;
	int		y;
	char	**tetromino;
	char	**map_ptr;

	y = -1;
	map_ptr = *map;
	while (map_ptr[++y])
	{
		x = -1;
		while (map_ptr[y][++x])
		{
			tetromino = ((t_tetris *)(list->content))->table;
			if ((map_ptr[y][x] == '.' || (map_ptr[y][x] != '.' && tetromino[0][0] == '.'))
				&& ft_check_place(list, map, x, y))
			{
				ft_place(list, map, x, y);
				if (list->next == NULL || ft_backtracking_solver(list->next, map))
					return (1);
				else
					ft_remove(list, map);
			}
		}
	}
	return (0);
}

char	**ft_fill_square(t_list *list, int	*size)
{
	char	**map;

	*size = ft_sqrt(4 * ft_list_len(list));
	map = ft_make_clear_map(*size);
	while (!ft_backtracking_solver(list, &map))
	{
		free(map);
		map = ft_make_clear_map((*size)++);
	}
	return (map);
}