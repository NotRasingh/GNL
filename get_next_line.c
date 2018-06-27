/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasingh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 10:28:16 by rasingh           #+#    #+#             */
/*   Updated: 2018/06/27 09:31:44 by rasingh          ###   ########.fr       */
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
	if (*ret == -1)
		return(NULL);
	tmp[*ret] = '\0';
	txt = buf;
	 if (buf[0] == '\0')
		buf = tmp;
	else
		buf = ft_strjoin(buf, tmp);
	//free (txt);
	return (buf);
}

int			get_next_line(const int fd, char **line)
{
	int			ret;
	int			i;
	char		*str;
	static char	*buf;
//	char		*str2;

	if (!line || fd < 0 || BUFF_SIZE <= 0)
		return (-1);
	if (buf == NULL)
		buf = ft_strnew(0);
	i = 0;
	ret = 1;
//	str2 = NULL;
	while (ret)
	{
		buf = ft_next(fd, buf, &ret);
		if (ret == -1)
			return (-1);
		if (ret == 0 && buf[0] == '\0')
			return (0);
		if ((str = ft_strchr(buf, '\n')))
		{
//			str2 = buf;
			str++;
			while (buf[i] != '\n')
				i++;
			*line = ft_strsub(buf, 0, i);
			ft_memmove(buf, str, ft_strlen(str) + 1);
//			buf = ft_strdup(str);
//			free (str2);
			return (1);
		}
/*		buf = ft_next(fd, buf, &ret);
		if (ret == -1)
		return (-1);
*/		if (!ft_strchr(buf, '\n'))
		{
//			str2 = buf;
			while (ret)
			{
//read your file till the end
			}
			*line = ft_strdup(buf);
//			buf = ft_strdup("");
//		free (str2);
//		  printf("First: %s\n", buf);
			return (0);
//				return (0);
		}
//		buf = ft_next(fd, buf, &ret);
	}
//	printf("LAST: %s", buf);
//	if (buf == NULL)
//		return (1);
		return (0);
}

/*int     main(int ac, char **av)
{
   (void)ac;
   int     fd;
   int     i;
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
   printf("%d\n", ret);
   }
   return (0);

}*/

/*int	main()
{
 char    *line;
    int     out;
    int     p[2];
    char    *str;
    int     gnl_ret;

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
	printf("%d\n", ft_strcmp(str, line));
	printf("%d\n", gnl_ret);
gnl_ret = get_next_line(p[0], &line);
printf("%d\n", gnl_ret);
printf("%s\n", line);

    //mt_assert(strcmp(line, "aaa") == 0);
    //mt_assert(gnl_ret == 0 || gnl_ret == 1);
}*/
