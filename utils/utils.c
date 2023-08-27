/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <abrin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 04:07:37 by abrin             #+#    #+#             */
/*   Updated: 2023/08/27 03:21:40 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strstr(char *big, char *lit)
{
	size_t	i;
	size_t	u;
	size_t	l;

	i = 0;
	l = ft_strlen(lit);
	if (l == 0)
		return (big);
	if (!big)
		return (NULL);
	while (big[i])
	{
		u = 0;
		while (big[i] && big[i + u] == lit[u])
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
	if (!str1 || !str2)
		return (-1);
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

char	*ft_strdup_special(t_data *data, const char *s)
{
	int		i;
	int		j;
	char	*dst;
	int		len;

	len = 0;
	i = 0;
	j = 1;
	while (s[len])
		len++;
	dst = gc_malloc(&data->gc, sizeof(char) * len + 3);
	if (dst == 0)
		return (NULL);
	dst[0] = '4';
	while (s[i] != '\0')
	{
		dst[j++] = s[i++];
	}
	dst[j] = '4';
	dst[j + 1] = '\0';
	return (dst);
}

int	ft_strnrchr(char *s, char *c)
{
	int		i;
	int		u;

	u = 0;
	i = 0;
	while (s[i] != '\0')
		i++;
	while (i >= 0 && s[i] != c[u])
	{
		i--;
		if (i < 0)
			return (0);
	}
	while (s[i] && c[i])
	{
		if (s[i] == c[u])
			u++;
		i++;
	}
	if (u == ft_strlen(c))
		return (1);
	return (0);
}

char	*ft_strdup(t_data *data, const char *s)
{
	int		i;
	char	*dst;
	int		len;

	len = 0;
	i = 0;
	while (s[len])
		len++;
	dst = gc_malloc(&data->gc, sizeof(char) * len + 1);
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
