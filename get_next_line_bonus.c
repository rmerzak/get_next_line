/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerzak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 12:07:04 by rmerzak           #+#    #+#             */
/*   Updated: 2021/12/06 13:58:07 by rmerzak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_line_with_n(char *str, int fd)
{
	char	*ret;
	int		p;

	ret = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!ret)
		return (NULL);
	p = 1;
	while (!ft_strchr(str, '\n') && p != 0)
	{
		p = read(fd, ret, BUFFER_SIZE);
		if (p == -1)
		{
			free(ret);
			return (NULL);
		}
		ret[p] = '\0';
		str = ft_strjoin(str, ret);
	}
	free(ret);
	return (str);
}

char	*ft_return_new_line(char *str)
{
	char	*s;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\n' && str[i])
		i++;
	s = (char *)malloc(sizeof(char) * (i + 2));
	if (!s)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		s[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		s[i++] = '\n';
	s[i] = '\0';
	return (s);
}

char	*ft_ptr_after_new_line(char *str)
{
	int		i;
	int		l;
	char	*s;

	i = 0;
	l = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	s = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!s)
		return (NULL);
	i++;
	while (str[i] != '\0')
		s[l++] = str[i++];
	s[l] = '\0';
	free(str);
	return (s);
}

char	*get_next_line(int fd)
{
	static char	*stati[10240];
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stati[fd] = get_line_with_n(stati[fd], fd);
	if (stati[fd] == NULL)
		return (NULL);
	str = ft_return_new_line(stati[fd]);
	stati[fd] = ft_ptr_after_new_line(stati[fd]);
	if (str[0] == '\0')
	{
		free(stati[fd]);
		free(str);
		return (NULL);
	}
	return (str);
}
