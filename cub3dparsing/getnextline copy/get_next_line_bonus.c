/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeltahi <haeltahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 10:30:57 by haeltahi          #+#    #+#             */
/*   Updated: 2023/08/12 20:03:15 by haeltahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read_to_left_str(int fd, char *left_str)
{
	char	*buf;
	int		chars_read;

	buf = malloc((BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	chars_read = 1;
	while (!ft_strchr(left_str, '\n') && chars_read != 0)
	{
		chars_read = read (fd, buf, BUFFER_SIZE);
		if (chars_read < 0)
		{
			free (left_str);
			free (buf);
			return (NULL);
		}
		buf[chars_read] = '\0';
		left_str = ft_strjoin(left_str, buf);
		if (!left_str)
			return (NULL);
	}
	free (buf);
	return (left_str);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*left_str[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	left_str[fd] = ft_read_to_left_str(fd, left_str[fd]);
	if (!left_str[fd])
		return (NULL);
	buff = printhatmany(left_str[fd]);
	left_str[fd] = remains(left_str[fd]);
	return (buff);
}
