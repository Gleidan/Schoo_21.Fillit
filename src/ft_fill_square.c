#include "fillit.h"

int		ft_sqrt(int nb)
{
	int result;

	result = 1;
	while (result * result < nb)
		result++;
	return (result);
}

void	ft_remove(t_list *tetromino, char ***map)
{
	int		x;
	int		y;
	int		count;
	char	**ptr;

	y = 0;
	count = 0;
	ptr = *map;
	while (ptr[y])
	{
		x = 0;
		while (ptr[y][x])
		{
			if (count == 4)
				return ;
			if (ptr[y][x] == ((t_tetris *)(tetromino->content))->letter && ++count)
				ptr[y][x] = '.';
			x++;
		}
		y++;
	}
}

int		ft_check_place(t_list *tetro, char ***map, int x, int y)
{
	int		x_plus;
	int		y_plus;
	int		block;
	char	**content;
	char	**ptr;

	ptr = *map;
	block = 0;
	y_plus = -1;
	content = ((t_tetris *)(tetro->content))->table;
	while (content[++y_plus])
	{
		x_plus = -1;
		while (content[y_plus][++x_plus])
		{
			if (!(ptr[y + y_plus]))
				return (0);
			if (ptr[y + y_plus][x + x_plus] == '.' && content[y_plus][x_plus] != '.')
				block++;
		}
	}
	return (block == 4);
}

int		ft_backtracking_solver(t_list *tetromino, char ***map)
{
	int		x;
	int		y;
	char	**tetro_block;
	char	**pointer;

	y = -1;
	pointer = *map;
	while (pointer[++y])
	{
		x = -1;
		while (pointer[y][++x])
		{
			tetro_block = ((t_tetris *)(tetromino->content))->table;
			if ((pointer[y][x] == '.' || (pointer[y][x] != '.' && tetro_block[0][0] == '.'))
				&& ft_check_place(tetromino, map, x, y))
			{
				ft_display(*map);
				ft_putchar('\n');
				if (tetromino->next == NULL || ft_backtracking_solver(tetromino->next, map))
					return (1);
				else
					ft_remove(tetromino, map);
			}
		}
	}
	return (0);
}

char	**ft_fill_square(t_list *tetromino)
{
	int		square_size;
	char	**map;

	square_size = ft_sqrt(4 * ft_list_len(tetromino));
	map = ft_make_clear_map(square_size);
	while (!ft_backtracking_solver(tetromino, &map))
	{
		free(map);
		map = ft_make_clear_map(square_size);
	}
	return (map);
}