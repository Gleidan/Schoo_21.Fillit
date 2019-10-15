#ifndef FILLIT_H
#define FILLIT_H
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>

#define TET_SIZE	5

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
	int 		placed;
	int 		skip;
	char		**table;
}				t_tetris;

void			ft_error(void);
void			ft_display(char **map);
char 			**ft_fill_square(t_list *list, int *size);
int				ft_check_buffer(char *buf, int bufflen);
int				ft_sqrt(int nb);
char 			**ft_make_clear_map(int size);
t_list			*ft_read_fd(int fd);
void			ft_free_list(void *content, size_t size);
int				ft_check_place(char **tetramino, char ***map, int x, int y);
int				ft_place(t_tetris *tetramino, char ***map, int x, int y);
void			ft_remove(t_tetris *tetramino, char ***map);
int				ft_backtracking_solver(t_list *tmp, char ***map);

#endif
