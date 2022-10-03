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

	len = 0;
	while (str[len])
	{
		if (!str[len] || str[len] == sep)
			break ;
		if (ft_strchr(str[len], "\'\""))
		{
			len++;
			while (str[len] && !ft_strchr(str[len], "'\""))
				len++;
			len++;
		}
		else if (!ft_strchr(str[len], "<>|"))
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
		while (++data->k < data->len)
			split[data->j][data->k] = str[data->i++];
	}
	return (split);
}

// char	**ft_split_string(char *str, char **split, char sep, t_split *data)
// {
// 	while (str[data->i])
// 	{
// 		ft_skip_sep(data, str, sep);
// 		data->len = ft_word_len(str, sep);
// 		split[++data->j] = ft_calloc(data->len + 2, sizeof(char));
// 		data->k = -1;
// 		while (++data->k < data->len && str[data->i] && str[data->i] != sep)
// 		{
// 			if (data->i < data->len && ft_strchr(str[data->i], "\'\""))
// 			{
// 				data->tok = str[data->i];
// 				split[data->j][data->k++] = str[data->i];
// 				data->i++;
// 				while (str[data->i] && data->k < data->len 
// 					&& str[data->i] != data->tok)
// 					split[data->j][data->k++] = str[data->i++];
// 			}
// 			if (data->i < data->len)
// 				split[data->j][data->k] = str[data->i++];
// 		}
// 		split[data->j][data->k] = '\0';
// 		if (str[data->i])
// 			data->i
// 		printf("split: %s\n", split[data->j]);
// 	}
// 	split[data->j + 1] = NULL;
// 	return (split);
// }

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
