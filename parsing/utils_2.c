/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:54:34 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/08/30 23:19:35 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	ft_isalpha(int c)
{
	if (c >= 65 && c <= 90)
		return (1);
	if (c >= 97 && c <= 122)
		return (1);
	else
		return (0);
}

void    *ft_calloc (size_t count, size_t size)
{
    unsigned int    len;
    void    *ptr;

    len = count * size;
    ptr = malloc(len * sizeof(char));
    if (!ptr)
        return NULL;
    ft_bzero(ptr, len);
    return ptr;
}

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
	total = ft_strlen(s1) + ft_strlen(s2) + 1;
	tab = (char *)ft_calloc(total + 1, sizeof(char));
	if (!tab)
		return (NULL);
	while (s1[i])
		tab[pos++] = s1[i++];
	i = 0;
	while (s2[i])
		tab[pos++] = s2[i++];
	return (tab);
}

char	*ft_strrchr(char *s, int c)
{
	size_t	i;
	char	ltr;

	ltr = (char)c;
	i = ft_strlen(s);
	if (s)
	{
		while (i)
		{
			if (s[i] == ltr)
				return ((char *)s + i);
			i--;
		}
		if (s[0] == ltr)
			return ((char *)s);
	}
	return (NULL);
}

int	wdlen_q(char *s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i] && ft_strncmp((char *)&s[i], &c, 1))
	{
		if (s[i] == '"')
		{
			i++;
			len++;
			while (s[i] != '"' && s[i])
			{
				len++;
				i++;
			}
			if (s[i] == '\0')
				return (len);
			len++;
		}
		else
			len++;
		i++;
	}
	return (len);
}

int	wdcount_q(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (ft_strchr(s[i], "\'\"") && s[i + 1] == '\0')
		return (1);
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{	
			while (ft_strchr(s[i], "\'\"") && s)
				i++;
			while (!ft_strchr(s[i], "\'\""))
				i++;
			while (ft_strchr(s[i], "\'\"") && s)
				i++;
			count++;
		}
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

char	**splitting_quotes(char *s, char c, int len, char **str)
{
	int		k;
	int		j;
	int		i;

	i = 0;
	j = -1;
	while (s[i])
	{
		while (s[i] && !ft_strncmp((char *)&s[i], &c, 1))
			i++;
		if (!s[i])
			break ;
		len = wdlen_q(s + i, c);
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

char	**ft_split_quotes(char *s, char c)
{
	char	**split;
	char	**str;

	if (!s)
		return (NULL);
	str = (char **)ft_calloc((wdcount_q(s, c) + 1), sizeof(char *));
	if (!str)
		return (NULL);
	split = splitting_quotes(s, c, 0, str);
	return (split);
}