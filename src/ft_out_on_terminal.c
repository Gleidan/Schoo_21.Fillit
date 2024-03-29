/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_out_on_terminal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanhack <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:36:51 by mmanhack          #+#    #+#             */
/*   Updated: 2019/10/17 16:37:28 by mmanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		ft_sqrt(int nb)
{
	int result;

	result = 1;
	while (result * result < nb)
		result++;
	return (result);
}

void	ft_error(void)
{
	ft_putstr("error\n");
	exit(0);
}

char	**ft_make_clear_map(int size)
{
	int		i;
	char	**map;

	if (!(map = malloc(sizeof(char *) * (size + 1))))
		ft_error();
	i = 0;
	while (i < size)
	{
		if (!(map[i] = malloc(sizeof(char) * (size + 1))))
			ft_error();
		map[i] = ft_memset(map[i], '.', size);
		map[i][size] = 0;
		i++;
	}
	map[i] = 0;
	return (map);
}

void	ft_display(char **map)
{
	if (!map || !*map)
		ft_error();
	while (*map)
	{
		ft_putstr(*(map++));
		ft_putchar('\n');
	}
}
