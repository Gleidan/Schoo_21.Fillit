/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reader_and_tab_maker.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanhack <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:50:56 by mmanhack          #+#    #+#             */
/*   Updated: 2019/10/17 16:53:00 by mmanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char		**ft_remove_usless(char **tab, int height)
{
	int		i;
	int		k;
	int		position;
	char	**temp;

	k = 0;
	i = -1;
	position = 4;
	if (!(temp = (char **)malloc(sizeof(char *) * (height + 1))))
		ft_error();
	while (tab[++i])
		if (ft_strchr(tab[i], '#') - tab[i] <= position)
			position = ft_strchr(tab[i], '#') - tab[i];
	i = -1;
	while (tab[++i])
		temp[k++] = ft_strsub(tab[i], position, TET_SIZE);
	temp[k] = 0;
	ft_clear_table(tab, height + 1);
	return (temp);
}

char		**ft_tetro_tab_creator(char *str, int height)
{
	int		counter_x;
	int		counter_y;
	char	**tmp;
	char	**tetro_tab;

	if (!(tetro_tab = (char **)malloc(sizeof(char *) * (height + 1))))
		ft_error();
	tmp = ft_strsplit(str, '\n');
	counter_x = 0;
	counter_y = -1;
	while (tmp[++counter_y])
	{
		if (ft_strchr(tmp[counter_y], '#'))
		{
			if (!(tetro_tab[counter_x++] = ft_strdup(tmp[counter_y])))
				ft_error();
		}
	}
	tetro_tab[counter_x] = 0;
	ft_clear_table(tmp, counter_y + 1);
	return (ft_remove_usless(tetro_tab, height));
}

int			ft_height(char *buf)
{
	int		h;
	int		c;

	h = 0;
	while (*buf)
	{
		c = 0;
		while (*buf != '\n' && *buf)
		{
			if (*buf == '#')
				c = 1;
			buf++;
		}
		if (c)
			h++;
		buf++;
	}
	return (h);
}

t_list		*ft_tetromino_creator(char *buf, char letter)
{
	t_list		*element;
	t_tetris	*tetromino;

	if (!(tetromino = (t_tetris *)malloc(sizeof(t_tetris))))
		ft_error();
	else
	{
		tetromino->height = ft_height(buf);
		tetromino->letter = letter;
		tetromino->table = ft_tetro_tab_creator(buf, tetromino->height);
		tetromino->width = ft_strlen(*tetromino->table);
		element = ft_lstnew(tetromino, sizeof(t_tetris));
		free(tetromino);
		return (element);
	}
	return (0);
}

t_list		*ft_read_fd(int fd)
{
	t_list	*list;
	char	buf[21 + 1];
	char	current_letter;
	int		end_fd;
	int		len;

	list = NULL;
	end_fd = 0;
	current_letter = 'A';
	while ((len = read(fd, buf, 21)))
	{
		buf[len] = '\0';
		if ((end_fd == 0 && (len != 20 && len != 21))
				|| (end_fd == 1 && len != 20))
			ft_error();
		if ((end_fd = ft_check_buffer(buf, len)) == -1)
			ft_error();
		if (list == NULL)
			ft_lstadd(&list, ft_tetromino_creator(buf, current_letter++));
		else
			ft_lstpushback(&list, ft_tetromino_creator(buf, current_letter++));
	}
	if (end_fd != 1 || ft_list_len(list) > 26)
		ft_error();
	return (list);
}
