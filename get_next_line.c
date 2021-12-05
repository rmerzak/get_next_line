/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerzak <rmerzak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 16:29:16 by rmerzak           #+#    #+#             */
/*   Updated: 2021/12/05 17:52:08 by rmerzak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
char	*get_line_with_n(char *str,int fd)
{
	char	*ret;
	int p;

	//ret = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	ret = malloc(BUFFER_SIZE + 1);
	if (!ret)
		return (NULL);
	p = 1;
	while (!ft_strchr(str,'\n') && p != 0)
	{
		if (fd == -1)
			return NULL;
		p = read(fd , ret, BUFFER_SIZE);
		if (p == -1)
		{
			free(ret);
			return NULL;
		}
		ret[p] = '\0';
		str = ft_strjoin(str,ret);
	}
	free(ret);
	return (str);
}

char	*ft_return_new_line(char *str)
{
	char	*s;
	int 	i;

	i = 0;
	if (str[0] == '\0')
		return (NULL);
	while (str[i] != '\n')
		i++;
	s = (char *)malloc(sizeof(char) * (i + 2));
	if (!s)
		return NULL;
	i = 0;
	while(str[i]!= '\n' && str[i] != '\0')
	{	
		s[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		s[i] = '\n';
	s[i] = '\0';
	return (s);
	
}

char *ft_ptr_after_new_line(char *str)
{
	int i;
	int l;
	char *s;
	
	i = 0;
	l = 0;
	while (str[i] != '\n')
		i++;
	while(str[i] != '\0')
	{
		l++;
		i++;
	}
	s = (char *)malloc(sizeof(char) * (l + 1));
	i = i - l + 1;
	l = 0;
	while (str[i] != '\0')
	{
		s[l]=str[i];
		i++;
		l++;
	}
	s[l] = '\0';
	free(str);
	return (s);
}
	

char	*get_next_line(int fd)
{
	static char	*Static;
	char		*str;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return NULL;
	Static = get_line_with_n(Static,fd);
	if (Static == NULL)
		return NULL;
	str = ft_return_new_line(Static);
	Static = ft_ptr_after_new_line(Static);
	return str;
}


// int main()
// {
// 	char *str;
// 	int fd;
// 	fd = open("42", O_RDONLY);

// 	str = get_next_line(fd);
// 	printf("%s\n",str);
// 	str = get_next_line(fd);
// 	printf("%s\n",str);
// 	str = get_next_line(fd);
// 	printf("%s\n",str);
// }
