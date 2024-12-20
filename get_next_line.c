/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahalle <flahalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:29:50 by flahalle          #+#    #+#             */
/*   Updated: 2024/12/20 16:37:39 by flahalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = '\0';
		i++;
	}
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	c = (unsigned char)c;
	if (!s)
		return (0);
	while (s[i])
	{
		if (((unsigned char *)s)[i] == c)
			return ((void *)(s + i));
		i++;
	}
	if (c == '\0')
		return ((void *)(s + i));
	return (NULL);
}

static char	*get_left(char *stash)
{
	if(ft_strchr(stash, '\n'))
		ft_strlcpy(stash, ft_strchr(stash, '\n') + 1, ft_strlen(stash, 0));
	else
		stash[0] = '\0';
	return (stash);
}

static char	*get_line(char *stash, int fd)
{
	char	*line;
	int		nbyte_read;

	nbyte_read = 1;
	line = NULL;
	line = ft_strdup("");
	if (!line)
		return (NULL);
	while (nbyte_read)
	{
		line = ft_strjoin(line, stash);
		if (!line)
			return (NULL);
		if (ft_strchr(line, '\n'))
			return (line);
		nbyte_read = read(fd, stash, BUFFER_SIZE);
		if(nbyte_read == 0 && stash[0] == '\0')
			return (free(line), NULL);
		stash[nbyte_read] = '\0';
		if (nbyte_read < 0)
			return (clear_buffer(stash, line), NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 1];

	char		*line;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = get_line(stash, fd);
	get_left(stash);
	if (!line)
		return (NULL);
	return (line);
}

int main(void)
{
    int fd;
    char *line;

    fd = open("giant_line_nl.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        return (1);
    }

    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    printf("%s", line);
    close(fd);
    return (0);
}
