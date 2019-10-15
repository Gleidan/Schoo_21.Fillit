#include "fillit.h"

int		ft_place(t_tetris *tetramino, char ***map, int x, int y)
{
	int		x_plus;
	int		y_plus;
	int		block;
	char	**tet_tab;
	char	**map_ptr;

	map_ptr = *map;
	block = 0;
	y_plus = -1;
	tet_tab = tetramino->table;
	while (tet_tab[++y_plus])
	{
		x_plus = -1;
		while (tet_tab[y_plus][++x_plus])
		{
			if (!(map_ptr[y + y_plus]))
				return (0);
			if (map_ptr[y + y_plus][x + x_plus] == '.' && tet_tab[y_plus][x_plus] != '.')
			{
				map_ptr[y + y_plus][x + x_plus] = tetramino->letter;
				tetramino->placed = 1;
				block++;
			}
		}
	}
	return (block == 4);
}

void	ft_remove(t_tetris *tetramino, char ***map)
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
			if (map_ptr[y][x] == tetramino->letter && ++count)
			{
				map_ptr[y][x] = '.';
				tetramino->placed = 0;
			}
			x++;
		}
		y++;
	}
}

int		ft_check_place(char **tetramino, char ***map, int x, int y)
{
	int		x_plus;
	int		y_plus;
	int		block;
	char	**map_ptr;

	map_ptr = *map;
	block = 0;
	y_plus = -1;
	while (tetramino[++y_plus])
	{
		x_plus = -1;
		while (tetramino[y_plus][++x_plus])
		{
			if (!(map_ptr[y + y_plus]))
				return (0);
			if (map_ptr[y + y_plus][x + x_plus] == '.' && tetramino[y_plus][x_plus] != '.')
				block++;
		}
	}
	return (block == 4);
}

int 	ft_optimal(char **map, int x, int y, t_tetris *tetramino)
{
	int 	count;
	int 	i;

	count = 0;
	i = 0;
	while (++i <= tetramino->width)
	{
		if (map[y][x] == '.')
			count++;
		x++;
	}
	return (count);
}

int		ft_backtracking_solver(t_list *list, char ***map)
{
	int			x;
	int			y;
	t_list		*tmp;
	t_tetris	*tetramino;
	char		**tet_tab;
	char		**map_ptr;

	tmp = list;
	while (((t_tetris *)(tmp->content))->placed == 1)
	{
		if (tmp->next == NULL)
			return (1);
		else
			tmp = tmp->next;
		while (((t_tetris *)(tmp->content))->skip == 1)
		{
			((t_tetris *)(tmp->content))->skip = 0;
			tmp = tmp->next;
		}
	}
	tetramino = (t_tetris *)(tmp->content);
	tet_tab = tetramino->table;
	y = -1;
	map_ptr = *map;
	while (map_ptr[++y])
	{
		x = -1;
		while (map_ptr[y][++x])
		{
			if ((map_ptr[y][x] == '.' || (map_ptr[y][x] != '.' && tet_tab[0][0] == '.'))
				&& ft_check_place(tet_tab, map, x, y))
			{
				ft_place(tetramino, map, x, y);
				if (ft_optimal(map_ptr, x, y, tetramino))
				{
					ft_remove(tetramino, map);
					tetramino->skip = 1;
					ft_backtracking_solver(list, map);
				}
//				ft_display(*map);
//				ft_putchar('\n');
				if (ft_backtracking_solver(list, map))
					return (1);
				else
					ft_remove(tetramino, map);
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