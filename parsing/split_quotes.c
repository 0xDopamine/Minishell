/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:19:11 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 05:35:16 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exec.h"

int	ft_qword_count(char *str, char sep)
{
	int	words;
	int	i;

	i = 0;
	words = 1;
	while (str[i++])
	{
		if (str[i] && str[i] == sep)
		{
			i++;
			words++;
		}
		if (ft_strchr(str[i], "\'\""))
		{
			if (str[i + 1] && ft_strchr(str[i], "\'\""))
				i++;
			while (str[i] && !ft_strchr(str[i], "\'\""))
				i++;
			if (!str[i])
				break ;
			i++;
		}
	}
	return (words);
}

int	ft_word_len(char *str, char sep)
{
	int	len;

	len = 0;
	while (str[len])
	{
		if (str[len] == sep)
			break ;
		if (ft_strchr(str[len], "\'\""))
		{
			len++;
			while (str[len] && !ft_strchr(str[len], "'\""))
				len++;
		}
		else
			len++;
	}
	return (len);
}

char	**ft_split_string(char *str, char **split, char sep)
{
	int		i;
	int		j;
	int		k;
	int		len;

	i = 0;
	j = -1;
	while (str[i])
	{
		while (str[i] && str[i] == sep)
			i++;
		len = ft_word_len(str, sep);
		split[++j] = ft_calloc(len + 1, sizeof(char));
		if (!*split)
		{
			freethis(split);
			return (NULL);
		}
		k = -1;
		while (++k < len)
			split[j][k] = str[i++];
	}
	return (split);
}

char	**ft_split_q(char *str, char sep)
{
	char	**split;

	split = ft_calloc((ft_qword_count(str, sep) + 1), sizeof(char *));
	if (!split)
		return (NULL);
	return (ft_split_string(str, split, sep));
}
