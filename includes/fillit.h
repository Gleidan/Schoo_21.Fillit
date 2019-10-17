/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanhack <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:33:05 by mmanhack          #+#    #+#             */
/*   Updated: 2019/10/17 16:34:20 by mmanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include "libft.h"
# include <unistd.h>
# include <fcntl.h>

# define TET_SIZE	5

typedef struct	s_size
{
	int			height;
	int			width;
}				t_size;

typedef struct	s_tetris
{
	int			width;
	int			height;
	char		letter;
	char		**table;
}				t_tetris;

void			ft_error(void);
void			ft_display(char **map);
char			**ft_fill_square(t_list *tetromino, int *size);
int				ft_check_buffer(char *buf, int bufflen);
int				ft_sqrt(int nb);
char			**ft_make_clear_map(int size);
t_list			*ft_read_fd(int fd);
void			ft_free_list(void *content, size_t size);

#endif
