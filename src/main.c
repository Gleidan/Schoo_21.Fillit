#include "fillit.h"

void	ft_free_tetro(t_tetris *tetromino, size_t size)
{
	if (!tetromino)
		return ;
	ft_clear_table(tetromino->table, tetromino->height + 1);
	free(tetromino);
	tetromino = NULL;
}


int		main(int argc, char **argv)
{
	int		fd;
	t_list	*list;
	char	**map;
	int		size;

	if (argc != 2)
	{
		ft_putstr("usage: fillit source file\n");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error();
	list = ft_read_fd(fd);
	map = ft_fill_square(list, &size);
	ft_display(map);
	ft_clear_table(map, size);
	ft_lstdel(&list, ft_free_tetro);
	close (fd);
	return (0);
}