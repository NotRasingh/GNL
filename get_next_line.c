/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasingh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 08:56:40 by rasingh           #+#    #+#             */
/*   Updated: 2018/06/29 14:36:03 by rasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(char *left, char **line)
{
	size_t	i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (left[i] != '\n' && left[i])
		i++;
	*line = ft_strsub(left, 0, i);
	if (ft_strchr(left, '\n') != NULL)
	{
		tmp2 = left;
		tmp = ft_strchr(left, '\n');
		tmp++;
		tmp = ft_strdup(tmp);
		free(tmp2);
	}
	else
	{
		tmp = ft_strdup("");
		tmp2 = left;
		free(tmp2);
	}
	return (tmp);
}

int		get_next_line(const int fd, char **line)
{
	static char *red;
	char		*tmp;
	char		buf[BUFF_SIZE + 1];
	int			ret;

	if (read(fd, buf, 0) < 0 || fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	if (red == NULL)
		red = ft_strdup("");
	while (ft_strchr(red, '\n') == NULL)
	{
		ret = read(fd, buf, BUFF_SIZE);
		if (ret == 0)
			break ;
		buf[ret] = '\0';
		tmp = red;
		red = ft_strjoin(red, buf);
		free(tmp);
	}
	if (ret == 0 && red[0] == '\0')
		return (0);
	red = ft_read(red, line);
	return (1);
}
