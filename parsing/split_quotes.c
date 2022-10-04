/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:19:11 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/28 20:01:46 by abaioumy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exec.h"

int	ft_qword_count(char *str, char sep)
{
	t_norm	norm;

	norm.i = 0;
	norm.words = 0;
	norm.should_increment = 1;
	while (str[norm.i])
	{
		if (str[norm.i] != sep && norm.should_increment)
		{
			norm.words++;
			norm.should_increment = 0;
		}
		if (ft_strchr(str[norm.i], "\'\""))
		{
			norm.tok = str[norm.i];
			while (str[norm.i] && str[norm.i] != norm.tok)
				norm.i++;
		}
		if (str[norm.i] == sep)
			norm.should_increment = 1;
		norm.i++;
	}
	return (norm.words);
}

int	ft_word_len(char *str, char sep)
{
	int	len;
	int	quote;

	len = 0;
	quote = 0;
	while (str[len])
	{
		if (!str[len] || str[len] == sep)
			break ;
		if (ft_strchr(str[len], "\'\""))
		{
			quote = str[len];
			len++;
			while (str[len] && str[len] != quote)
				len++;
		}
		else if (!ft_strchr(str[len], "<>|"))
			len++;
		if (!str[len])
			break ;
		else
			len++;
	}
	return (len);
}

void	ft_skip_sep(t_split *data, char *str, char sep)
{
	while (str[data->i] && str[data->i] == sep)
		data->i++;
}

char	**ft_split_string(char *str, char **split, char sep, t_split *data)
{
	while (str[data->i])
	{
		if (!str[data->i])
			break ;
		while (str[data->i] && str[data->i] == sep)
			data->i++;
		data->len = ft_word_len(str + data->i, sep);
		split[++data->j] = (char *)ft_calloc(data->len + 1, sizeof(char));
		data->k = -1;
		while (++data->k < data->len && str[data->i] != sep)
		{
			if (ft_strchr(str[data->i], "\'\""))
			{
				while (data->k < data->len)
					split[data->j][data->k++] = str[data->i++];
			}
			else
				split[data->j][data->k] = str[data->i++];
		}
	}
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
