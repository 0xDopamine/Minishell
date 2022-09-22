/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 02:07:43 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/22 16:50:22 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*tab;
	size_t	total;
	int		i;
	int		pos;

	pos = 0;
	i = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	total = ft_strlen(s1) + ft_strlen(s2) + 1;
	tab = (char *)calloc(total, sizeof(char));
	if (!tab)
		return (NULL);
	while (s1[i])
		tab[pos++] = s1[i++];
	i = 0;
	while (s2[i])
		tab[pos++] = s2[i++];
	return (tab);
}

int	wdlen(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && ft_strncmp((char *)&s[i], &c, 1))
		i++;
	return (i);
}

int	wdcount(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count += 1;
		i++;
	}
	return (count);
}

char	**splitting(char *s, char c, int len, char **str)
{
	int		k;
	int		j;
	int		i;

	i = 0;
	j = -1;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		len = wdlen(s + i, c);
		str[++j] = (char *)ft_calloc(len + 1, sizeof(char));
		if (!str[j])
		{
			freethis(str);
			return (NULL);
		}
		k = -1;
		while (++k < len)
			str[j][k] = s[i++];
	}
	return (str);
}

char	**ft_split(char *s, char c)
{
	char	**split;
	char	**str;

	if (!s)
		return (NULL);
	str = (char **)ft_calloc((wdcount(s, c) + 1), sizeof(char *));
	if (!str)
		return (NULL);
	split = splitting(s, c, 0, str);
	return (split);
}
