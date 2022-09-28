/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:19:11 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/28 20:01:46 by codespace        ###   ########.fr       */
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

char	**ft_split_string(char *str, char **split, char sep, t_split *data)
{
	while (str[data->i])
	{
		while (str[data->i] && str[data->i] == sep)
			data->i++;
		data->len = ft_word_len(str, sep);
		split[++data->j] = ft_calloc(data->len + 2, sizeof(char));
		if (!*split)
		{
			freethis(split);
			return (NULL);
		}
		data->k = -1;
		while (++data->k < data->len && str[data->i] && str[data->i] != sep)
		{
			if (ft_strchr(str[data->i], "\'\""))
			{
				data->tok = str[data->i];
				split[data->j][data->k++] = str[data->i];
				data->i++;
				while (data->k < data->len && str[data->i]
					&& str[data->i] != data->tok)
					split[data->j][data->k++] = str[data->i++];
			}
			split[data->j][data->k] = str[data->i++];
		}
		split[data->j][data->k] = '\0';
		if (str[data->i])
			data->i++;
	}
	split[data->j + 1] = NULL;
	return (split);
}

char	**ft_split_q(char *str, char sep)
{
	char	**split;
	char	**ret;
	t_split	*data;

	if (ft_strchr(*str, "\'\""))
		ft_check_quotes(&str);
	if (!str)
		return (NULL);
	ret = NULL;
	data = malloc(sizeof(t_data));
	data->i = 0;
	data->j = -1;
	split = ft_calloc((ft_qword_count(str, sep) + 2), sizeof(char *));
	ret = ft_split_string(str, split, sep, data);
	free(data);
	return (ret);
}
