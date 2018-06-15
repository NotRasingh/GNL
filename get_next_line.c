/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasingh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 10:28:16 by rasingh           #+#    #+#             */
/*   Updated: 2018/06/15 13:35:00 by rasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
static char	*ft_next(const int fd, char *buf, int *ret)
{
	 char	*txt;
	 char	*tmp;

	if (!(tmp = (char*)malloc(BUFF_SIZE + 1)))
		return (NULL);
	*ret = read(fd, tmp, BUFF_SIZE);
	tmp[*ret] = '\0';
	txt = buf;
	buf = ft_strjoin(buf, tmp);
	ft_strdel((char**)(&txt));
	return (buf);
}

int			get_next_line(const int fd, char **line)
{
	static int	ret;
	int			i;
	char		*str;
	static char	*buf;

	if (!(line) || fd < 0 || BUFF_SIZE <= 0)
		return (-1);
	if (buf == NULL)
		buf = ft_strnew(0);
	i = 0;
	ret = 1;
	while (ret)
	{
//		printf("HI\n");
		if ((str = ft_strchr(buf, '\n')))
		{
			str++;
			while (buf[i] != '\n' && buf)
				i++;
			*line = ft_strsub(buf, 0, i);
			ft_memmove(buf, str, ft_strlen(str) + 1);
			return (1);
		}
		buf = ft_next(fd, buf, &ret);
//		printf("%s\n", buf);
		if (ret == -1)
			return (-1);
		if ((str = ft_strchr(buf, '\0')) && !ret)
		{
//			printf("BI\n");
			i = 0;
			*line = ft_strdup(buf);
//			printf("%s\n", *line);
			return (0);
		}
	}
	return (0);
}

int     main()//(int ac, char **av)
{
      int     out;
    int     p[2];
    char    *str;
    int     gnl_ret;
	char  	*line = NULL;

    str = (char *)malloc(1000 * 1000);
    *str = '\0';
    strcat(str, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur in leo dignissim, gravida leo id, imperdiet urna. Aliquam magna nunc, maximus quis eleifend et, scelerisque non dolor. Suspendisse augue augue, tempus");
    strcat(str, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur in leo dignissim, gravida leo id, imperdiet urna. Aliquam magna nunc, maximus quis eleifend et, scelerisque non dolor. Suspendisse augue augue, tempus");
    strcat(str, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur in leo dignissim, gravida leo id, imperdiet urna. Aliquam magna nunc, maximus quis eleifend et, scelerisque non dolor. Suspendisse augue augue, tempus");
    out = dup(1);
    pipe(p);
    dup2(p[1], 1);

    write(1, str, strlen(str));
    close(p[1]);
    dup2(out, 1);
    gnl_ret = get_next_line(p[0], &line);
	printf("%s\n", line);
	printf("%d", ft_strcmp(line, str));
	printf("%d", gnl_ret);
}
