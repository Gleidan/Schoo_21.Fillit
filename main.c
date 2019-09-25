/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconcent <jconcent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 11:25:08 by jconcent          #+#    #+#             */
/*   Updated: 2019/09/25 11:49:27 by jconcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int 	main(int argc, char **argv)
{
	int fd;

	if (argc != 2)
	{
		ft_putstr("usage\n");
		return (0);
	}
	fd = open(av[1], O_RDONLY);
	if (fd = -1)
		ft_error_fd();
	ft_read_fd(fd);
	return (0);
}