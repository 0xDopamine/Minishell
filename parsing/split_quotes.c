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
	int	words;
	int should_increment;
	int	i;
	int	tok;

	i = 0;
	words = 0;
	should_increment = 1;
	

	while (str[i])
	{
		if (str[i] != sep && should_increment)
		{
			words++;
			should_increment = 0;
		}
		if (ft_strchr(str[i], "\'\""))
		{
			tok = str[i];
			while (str[i] && str[i] != tok)
				i++;
		}
		if (str[i] == sep)
			should_increment = 1;
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
		ft_skip_sep(data, str, sep);
		data->len = ft_word_len(str, sep);
		split[++data->j] = ft_calloc(data->len + 2, sizeof(char));
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
	printf("split: %s\n", split[data->j]);
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
	int rret = ft_qword_count(str, sep);
	printf("%d\n", rret);
	split = ft_calloc((rret + 2), sizeof(char *));
	ret = ft_split_string(str, split, sep, data);
	free(data);
	return (ret);
}
