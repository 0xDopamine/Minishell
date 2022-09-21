/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 02:14:07 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 02:30:13 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	check(char before, char after)
{
	if (ft_strchr(before, " \t\r\v\n\f") || ft_strchr(after, " \t\r\v\n\f"))
		return (1);
	else
		return (0);
}

char	*handle_spaces(char *line)
{
	int		i;
	int		count;
	int		index;

	i = 0;
	count = 0;
	index = 0;
	while (line[i])
	{
		if (ft_strchr(line[i], "|<>"))
		{
			if (line[i] == '>' && line[i + 1] == '>')
			{
				if (!check(line[i - 1], line[i + 2]) && line)
					count += 2;
			}
			else if (line[i - 1] != ' ' || line[i + 1] != ' ')
					count += 1;
		}
		i++;
	}
	if (count > 0)
		return (add_spaces(line, count));
	return (line);
}

char	*spaces(char *line)
{
	int	i;

	i = 0;
	if (ft_strlen(line) == 1)
		return (line);
	while (line[i])
	{
		if (line[i] == '|')
			if (line[i - 1] != ' ' || line[i + 1] != ' ')
				return (handle_spaces(line));
		i++;
	}
	return (line);
}

char	*add_spaces(char *line, int count)
{
	t_space	space;

	space.i = 0;
	space.j = 0;
	space.len = ft_strlen(line);
	space.str = malloc(sizeof(char) * (space.len + (count * 2) + 1));
	space.str = loop_spaces(space, line);
	free(line);
	return (space.str);
}

char	*loop_spaces(t_space space, char *line)
{
	while (line[space.i])
	{
		if (ft_strchr(line[space.i], "|<>"))
		{
			space.str[space.j] = ' ';
			if (line[space.i] == '>' && line[space.i + 1] == '>')
			{
				space.str[space.j + 1] = line[space.i];
				space.str[space.j + 2] = line[space.i + 1];
				space.str[space.j + 3] = ' ';
				space.j += 4;
				space.i += 2;
			}
			else
			{
				space.str[space.j + 1] = line[space.i++];
				space.str[space.j + 2] = ' ';
				space.j += 3;
			}
		}
		else
			space.str[space.j++] = line[space.i++];
	}
	space.str[space.j] = '\0';
	return (space.str);
}
