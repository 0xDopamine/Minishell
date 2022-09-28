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
