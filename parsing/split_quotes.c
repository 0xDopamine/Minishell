/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:19:11 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/23 05:37:04 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exec.h"

int	ft_qword_count(char *str, char sep)
{
	int	words;
	int	i;
	int	tok;

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
			tok = str[i];
			while (str[i] && str[i] != tok)
				i++;
		}
		else if (str[i])
			i++;
	}
	printf("words: %d\n", words);
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
	int		tok;

	i = 0;
	j = -1;
	while (str[i])
	{
		while (str[i] && str[i] == sep)
			i++;
		len = ft_word_len(str, sep);
		split[++j] = ft_calloc(len + 2, sizeof(char));
		if (!*split)
		{
			freethis(split);
			return (NULL);
		}
		k = -1;
		while (++k < len && str[i] && str[i] != sep)
		{
			if (ft_strchr(str[i], "\'\""))
			{
				tok = str[i];
				split[j][k++] = str[i];
				i++;
				while (k < len && str[i] && str[i] != tok)
					split[j][k++] = str[i++];
			}
			split[j][k] = str[i++];
		}
		split[j][k] = '\0';
		if (str[i])
			i++;
	}
	split[j + 1] = NULL;
	return (split);
}

char	**ft_split_q(char *str, char sep)
{
	char	**split;

	split = ft_calloc((ft_qword_count(str, sep) + 2), sizeof(char *));
	if (!split)
		return (NULL);
	return (ft_split_string(str, split, sep));
}
