/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeltahi <haeltahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 10:31:46 by haeltahi          #+#    #+#             */
/*   Updated: 2024/10/20 19:25:42 by haeltahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	i;
	size_t	total_len;

	i = 0;
	if (!s1)
	{
		s1 = malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	total_len = ft_strlen(s1) + ft_strlen(s2);
	new = malloc(sizeof(char) * total_len + 1);
	if (!new)
		return (NULL);
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (*s2)
		new[i++] = *s2++;
	new[i] = '\0';
	free(s1);
	return (new);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*printhatmany(char *left_str)
{
	char	*buf;
	int		i;

	i = 0;
	if (!left_str[i])
	{
		return (NULL);
	}
	while (left_str[i] && left_str[i] != '\n')
		i++;
	buf = malloc(i + 2);
	if (!(buf))
		return (NULL);
	i = 0;
	while (left_str[i] != '\n' && left_str[i] != '\0')
	{
		buf[i] = left_str[i];
		i++;
	}
	if (left_str[i] == '\n')
		buf[i++] = '\n';
	buf[i] = '\0';
	return (buf);
}

char	*remains(char *left_str)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (left_str[i] && left_str[i] != '\n')
		i++;
	if (!left_str[i])
	{
		free(left_str);
		return (NULL);
	}
	if (left_str[i] == '\n')
		i++;
	new = malloc(ft_strlen(left_str) - i + 1);
	if (!new)
		return (NULL);
	while (left_str[i])
		new[j++] = left_str[i++]; 
	new[j] = '\0';
	free (left_str);
	return (new);
}
