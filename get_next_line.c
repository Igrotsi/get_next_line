/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahalle <flahalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:29:50 by flahalle          #+#    #+#             */
/*   Updated: 2024/12/18 19:07:41 by flahalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strchr(char *s, int c)
{
	size_t	i;

	i = 0;
	c = (unsigned char)c;
	if (!s)
		return (0);
	while (s[i])
	{
		if (((unsigned char *)s)[i] == c)
			return (1);
		i++;
	}
	if (c == '\0')
		return (0);
	return (0);
}

static void	get_left(char *stash)
{
	char	*temp;

	temp = ft_substr(stash, ft_strlen(stash, '\n'), ft_strlen(stash, '\0')
			- ft_strlen(stash, '\n'));
	ft_strlcpy(stash, temp, ft_strlen(temp, 0));
	//printf("%s", stash);
	free(temp);
}

static char	*get_line(char *stash, int fd)
{
	char	*temp;
	int		nbyte_read;

	nbyte_read = 1;
	temp = NULL;
	if (stash && stash[0])
		temp = ft_strjoin(temp, stash);
	if (ft_strchr(temp, '\n'))
	{
		return (temp);
	}
	while (nbyte_read)
	{
		nbyte_read = read(fd, stash, BUFFER_SIZE);
		if (nbyte_read == -1)
			return (NULL);
		if (nbyte_read == 0)
			break ;
		stash[nbyte_read] = '\0';
		temp = ft_strjoin(temp, stash);
		if (ft_strchr(stash, '\n'))
			break ;
	}
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 1];
	char		*line;

	if (!fd)
		return (NULL);
	line = get_line(stash, fd);
	if (!line)
		return (NULL);
	get_left(stash);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*ligne;

// 	fd = open("file", O_RDONLY);
// 	ligne = get_next_line(fd);
// 	printf(" test %s", ligne);
// 	free(ligne);
// 	ligne = get_next_line(fd);
// 	printf(" test %s", ligne);
// 	free(ligne);
// 	ligne = get_next_line(fd);
// 	printf(" test %s", ligne);
// 	free(ligne);
// }
