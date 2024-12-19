/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahalle <flahalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:29:55 by flahalle          #+#    #+#             */
/*   Updated: 2024/12/19 19:18:45 by flahalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(char *s)
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char *)malloc(sizeof(char) * ft_strlen(s, 0) + 1);
	if (dest == NULL)
		return (0);
	else
	{
		while (s[i])
		{
			dest[i] = s[i];
			i++;
		}
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*s3;

	i = 0;
	j = 0;
	s3 = (char *)malloc(sizeof(char) * (ft_strlen(s1, 0) + ft_strlen(s2, '\n')
				+ 1) + ft_strchr(s2, '\n'));
	if (s3 == NULL)
	{
		free(s1);
		return (NULL);
	}
	while (s1 && s1[i])
		s3[j++] = s1[i++];
	i = 0;
	while (s2[i] && s2[i] != '\n')
		s3[j++] = s2[i++];
	if (s2[i] == '\n')
		s3[j++] = '\n';
	s3[j] = '\0';
	free(s1);
	return (s3);
}

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		dest[0] = '\0';
	while (src[i] != '\0' && i < size)
	{
		dest[i] = src[i];
		i++;
	}
	if (size > 0)
		dest[i] = '\0';
	return (ft_strlen(src, 0));
}

size_t	ft_strlen(char *str, char c)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != 0 && str[i] != c)
	{
		i++;
	}
	if (str[i] == c && c != '\0')
		i++;
	return (i);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	slen;

	slen = ft_strlen(s, 0);
	if (!s)
		return (NULL);
	if (start >= slen)
		return (ft_strdup(""));
	if (start + len > slen)
		len = slen - start;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s + start, len + 1);
	return (result);
}
