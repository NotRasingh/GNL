/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasingh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 14:41:39 by rasingh           #+#    #+#             */
/*   Updated: 2018/06/29 14:44:23 by rasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int     main(int ac, char **av)
{
	(void)ac;
	int     fd;
	int     ret;
	char    *line = NULL;

	ret = 1;
	if ((fd = open(av[1],O_RDONLY)) == -1)
	{
		printf("could not open file\n");
		return (0);
	}
	// ret = get_next_line(fd,&line);
	// printf(“%s”,line);
	while (ret)
	{
		ret = get_next_line(fd,&line);
		if (ret)
			printf("%s\n",line);
		///       free(line);
		//  printf("%d\n", ret);
	}
	return (0);
}
