/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahalle <flahalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:29:50 by flahalle          #+#    #+#             */
/*   Updated: 2024/12/19 20:13:45 by flahalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_bzero(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = '\0';
		i++;
	}
}

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

static char	*get_left(char *stash)
{
	char	*temp;

	temp = ft_substr(stash, ft_strlen(stash, '\n'), ft_strlen(stash, '\0')
			- ft_strlen(stash, '\n'));
	if (!temp)
		return (NULL);
	ft_strlcpy(stash, temp, ft_strlen(temp, 0));
	free(temp);
	return (stash);
}

static char	*get_line(char *stash, int fd)
{
	char	*temp;
	int		nbyte_read;

	nbyte_read = 1;
	temp = NULL;
	if (stash && stash[0])
	{
		temp = ft_strjoin(temp, stash);
		if (!temp)
			return (NULL);
	}
	if (ft_strchr(temp, '\n'))
		return (temp);
	while (nbyte_read)
	{
		nbyte_read = read(fd, stash, BUFFER_SIZE);
		stash[nbyte_read] = '\0';
		if (nbyte_read == -1)
		{
			ft_bzero(stash);
			free(temp);
			return (NULL);
		}
		if (nbyte_read == 0)
			break ;
		temp = ft_strjoin(temp, stash);
		if (!temp)
			return (NULL);
		if (ft_strchr(stash, '\n'))
			return (temp);
	}
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0)
		return (NULL);
	line = get_line(stash, fd);
	if (!line)
		return (NULL);
	if (!get_left(stash))
	{
		free(line);
		return (NULL);
	}
	return (line);
}

// int main(void)
// {
//     int fd;
//     char *line;

//     fd = open("file", O_RDONLY);
//     if (fd == -1)
//     {
//         printf("Erreur lors de l'ouverture du fichier\n");
//         return (1);
//     }

//     while ((line = get_next_line(fd)))
//     {
//         printf("%s", line);
//         free(line);
//     }
//     printf("%s", line);
//     close(fd);
//     return (0);
// }
