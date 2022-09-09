/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 02:04:26 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/09 21:20:35 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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
			while (ft_strchr(s[i], "\'\"") && s[i])
				i++;
			while (!ft_strchr(s[i], "\'\"") && s[i])
				i++;
			while (ft_strchr(s[i], "\'\"") && s[i])
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
