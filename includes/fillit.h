#ifndef FILLIT_H
#define FILLIT_H
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>

typedef struct	s_size
{
	int			height;
	int			width;
} 				t_size;

typedef struct	s_tetris
{
	int			width;
	int			height;
	char		letter;
	char		**table;
}				t_tetris;

void			ft_error(void);
void			ft_display(char **map);
char 			**ft_fill_square(t_list *tetromino, int *size);
int				ft_check_buffer(char *buf, int bufflen);
int				ft_sqrt(int nb);
char 			**ft_make_clear_map(int size);
t_list			*ft_read_fd(int fd);

#endif
