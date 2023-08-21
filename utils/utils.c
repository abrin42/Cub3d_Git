/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarie <tmarie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 04:07:37 by abrin             #+#    #+#             */
/*   Updated: 2023/08/21 23:37:52 by tmarie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_strchr(char *string)
{
	char	c;
	int		i;

	i = 0;
	c = '\n';
	if (!string)
		return (0);
	while (string[i] != '\0')
	{
		if (string[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strnstr(char *big, char *lit, size_t len)
{
	size_t	i;
	size_t	u;
	size_t	l;

	i = 0;
	l = ft_strlen(lit);
	if (l == 0)
		return (big);
	if (!big)
		return(NULL);
	while (big[i] && i < len)
	{
		u = 0;
		while (big[i] && i + u < len && big[i + u] == lit[u])
		{
			u++;
			if (u == l)
				return (&big[i]);
		}
		i++;
	}
	return (NULL);
}

int	ft_strncmp(char *str1, char *str2, int length)
{
	int	i;

	i = 0;
	while (str1[i] != '\0' && i < length)
	{
		if (!(str1[i] == str2[i]))
			return (str1[i] - str2[i]);
		i++;
	}
	if (str2[i] == '\0' || i == length)
		return (0);
	else
		return (str1[i] - str2[i]);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dst;
	int		len;

	len = 0;
	i = 0;
	while (s[len])
		len++;
	dst = malloc (sizeof(char) * len + 1);
	if (dst == 0)
		return (NULL);
	while (s[i] != '\0')
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
