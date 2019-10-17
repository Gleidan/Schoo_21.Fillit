/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_square.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanhack <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:39:02 by mmanhack          #+#    #+#             */
/*   Updated: 2019/10/17 16:50:46 by mmanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		ft_place(t_list *list, char ***map, int x, int y)
{
	int		xx;
	int		yy;
	int		block;
	char	**tab;
	char	**ptr;

	ptr = *map;
	block = 0;
	yy = -1;
	tab = ((t_tetris *)(list->content))->table;
	while (tab[++yy])
	{
		xx = -1;
		while (tab[yy][++xx])
		{
			if (!(ptr[y + yy]))
				return (0);
			if (ptr[y + yy][x + xx] == '.' && tab[yy][xx] != '.')
			{
				ptr[y + yy][x + xx] = ((t_tetris*)(list->content))->letter;
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
			if (ptr[y][x] == ((t_tetris*)(list->content))->letter && ++count)
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
			if (ptr[y + y_plus][x + x_plus] == '.'
					&& content[y_plus][x_plus] != '.')
				block++;
		}
	}
	return (block == 4);
}

int		ft_solver(t_list *list, char ***map)
{
	int		x;
	int		y;
	char	**tet_tab;
	char	**map_p;

	y = -1;
	map_p = *map;
	while (map_p[++y])
	{
		x = -1;
		while (map_p[y][++x])
		{
			tet_tab = ((t_tetris *)(list->content))->table;
			if ((map_p[y][x] == '.' || (map_p[y][x] != '.'
				&& tet_tab[0][0] == '.')) && ft_check_place(list, map, x, y))
			{
				ft_place(list, map, x, y);
				if (list->next == NULL || ft_solver(list->next, map))
					return (1);
				else
					ft_remove(list, map);
			}
		}
	}
	return (0);
}

char	**ft_fill_square(t_list *tetromino, int *size)
{
	char	**map;

	*size = ft_sqrt(4 * ft_list_len(tetromino));
	map = ft_make_clear_map(*size);
	while (!ft_solver(tetromino, &map))
	{
		free(map);
		map = ft_make_clear_map((*size)++);
	}
	return (map);
}
