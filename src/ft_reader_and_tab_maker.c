#include "fillit.h"

char		**ft_remove_usless(char **tab, int width, int height)
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
		temp[k++] = ft_strsub(tab[i], position, width);
	temp[k] = 0;
	ft_clear_table(tab, height + 1);
	return (temp);
}

char		**ft_tetro_tab_creator(char *str, int height, int width)
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
			if (!(tetro_tab[counter_x] = (char *)malloc(sizeof(char) * 5)))
				ft_error();
			tetro_tab[counter_x++] = ft_strdup(tmp[counter_y]);
		}
	}
	tetro_tab[counter_x] = 0;
	ft_clear_table(tmp, counter_y + 1);
	return (ft_remove_usless(tetro_tab, width, height));
}

t_size		*ft_get_size(char *buf)
{
	int		count;
	int		tmp;
	t_size	*size;

	if (!(size = malloc(sizeof(t_size))))
		ft_error();
	size->height = 0;
	size->width = 0;
	tmp = 0;
	count = -1;
	while (buf[++count])
	{
		if (buf[count] == '\n' && ++size->height && (size->width = (tmp > size->width) ? tmp : size->width))
			tmp = 0;
		else if (buf[count] == '#')
			tmp++;
		if ((buf[count] == '\n' || buf[count] == '.') || (buf[count + 3] == '#' &&
			(buf[count + 4] == '#' || buf[count + 2] == '#')) ||
			(buf[count + 6] == '#' && (buf[count + 7] == '#' || buf[count + 5])))
			tmp++;
	}
	size->width = (tmp > size->width) ? tmp : size->width;
	size->height++;
	return (size);
}

t_list		*ft_tetromino_creator(char *buf, char letter)
{
	t_list		*element;
	t_tetris	*tetromino;
	t_size		*size;
	char		*copy;
	long		pos;

	if (!(tetromino = (t_tetris *)malloc(sizeof(t_tetris))))
		ft_error();
	pos = ft_strchr(buf, '#') - buf;
	copy = ft_strsub(buf, pos, (ft_strrchr(buf, '#') - buf + 1) - pos);
	size = ft_get_size(copy);
	tetromino->width =  size->width;
	tetromino->height = size->height;
	tetromino->letter = letter;
	tetromino->table = ft_tetro_tab_creator(buf, tetromino->height, tetromino->width);
	element = ft_lstnew(tetromino, sizeof(t_tetris));
	free(copy);
	free(size);
	return (element);
}

t_list		*ft_read_fd(int fd)
{
	t_list	*list;
	char	buffer[21 + 1];
	char	current_letter;
	int		end_fd;
	int		len;

	list = NULL;
	end_fd = 0;
	current_letter = 'A';
	while ((len = read(fd, buffer, 21)))
	{
		buffer[len] = '\0';
		if ((end_fd == 0 && (len != 20 && len != 21)) || (end_fd == 1 && len != 20))
			ft_error();
		if ((end_fd = ft_check_buffer(buffer, len)) == -1)
			ft_error();
		if (list == NULL)
			ft_lstadd(&list, ft_tetromino_creator(buffer, current_letter++));
		else
			ft_lstpushback(&list, ft_tetromino_creator(buffer, current_letter++));
	}
	if (end_fd != 1 || ft_list_len(list) > 26)
		ft_error();
	return (list);
}