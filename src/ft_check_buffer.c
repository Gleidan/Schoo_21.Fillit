#include "fillit.h"

int		ft_check_sqr(char *buffer, int i)
{
	int contact_checked;

	contact_checked = 0;
	if (i >= 1 && buffer[i - 1] == '#')
		contact_checked++;
	if (i >= 4 && buffer[i - 5] == '#')
		contact_checked++;
	if (i <= 14 && buffer[i + 5] == '#')
		contact_checked++;
	if (i <= 19 && buffer[i + 1] == '#')
		contact_checked++;
	if (contact_checked != 1 && contact_checked != 2 && contact_checked != 3)
		return (-100);
	return (contact_checked);
}

int		ft_check_dot(char *str)
{
	int dots;

	dots = 0;
	while (*str)
	{
		if (*str == '.')
			dots++;
		str++;
	}
	return (dots == 12);
}

int		ft_check_buffer(char *buf, int bufflen)
{
	int	newline;
	int sharp;
	int count;

	newline = 0;
	count = 0;
	sharp = 0;
	while (count < bufflen)
	{
		if ((buf[count] == '\n' && (count + 1) % 5 != 0) ||
				((buf[count] != '#' || buf[count] != '.') && (count + 1) % 5 == 0))
			return (-1);
		if (buf[count] == '#')
			sharp += ft_check_sqr(buf, count);
		count++;
		while (buf[count] == '\n' && count < bufflen)
		{
			count++;
			newline++;
		}
	}
	if (!ft_check_dot(buf) || (sharp != 6 && sharp != 8))
		return (-1);
	return (newline == 4 ? 0 : 1);
}