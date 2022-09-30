/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 17:25:18 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/23 18:50:10 by abaioumy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	freethis(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	freethis1(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		freethis(&str[i]);
		i++;
	}
	freethis(str);
}

int	ft_is_heredoc(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<' && line[i + 1] == '<')
			return (1);
		i++;
	}
	return (0);
}

int	ft_space_count(char *line, int i, int count)
{
	if ((line[i] == '>' && line[i + 1] == '>'))
	{
		if (!check(line[i - 1], line[i + 2]) && line)
			count += 3;
	}
	else if (i > 0 && (line[i - 1] != ' ' || line[i + 1] != ' '))
			count += 2;
	return (count);
}

void	ft_free_and_null(t_parse *parse, int flag)
{
	if (flag)
	{
		freethis(parse->split);
		parse->split = NULL;
	}
	else
	{
		free(parse->state);
		parse->state = NULL;
	}
}
