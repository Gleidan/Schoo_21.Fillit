#include "fillit.h"

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
	close (fd);
	return (0);
}