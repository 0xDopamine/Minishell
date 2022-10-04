/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 02:14:07 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/28 22:39:05 by abaioumy        ###   ########.fr       */
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
	char	*temp;

	i = 0;
	count = 1;
	while (line[i++])
	{
		if (i > 0 && ft_strchr(line[i], "|<>"))
			count = ft_space_count(line, i, count);
	}
	if (count > 0)
	{
		temp = (line);
		line = add_spaces(temp, count);
		return (line);
	}
	return (line);
}

char	*free_line_spaces(char *line)
{
	free(line);
	return (NULL);
}

char	*spaces_protection(char *line)
{
	if (!line)
		return (free_line_spaces(line));
	if (ft_strlen(line) == 1)
		return (ft_strdup(line));
	return (NULL);
}

char	*spaces(char *line)
{
	t_split sp;

	sp.i = 0;
	if (!line || ft_strlen(line) == 1)
		return (spaces_protection(line));
	while (line[sp.i])
	{
		if (line[sp.i] && ft_strchr(line[sp.i], "\'\""))
		{
			sp.tok = line[sp.i];
			sp.i++;
			while (line[sp.i] && line[sp.i] != sp.tok)
				sp.i++;
		}
		else if (ft_strchr(line[sp.i], "|<>") && !ft_is_heredoc(line))
		{
			if (sp.i > 0 && (line[sp.i - 1] != ' ' || line[sp.i + 1] != ' '))
			{
				line = handle_spaces(line);
				return (line);
			}
			sp.i++;
		}
		else
			sp.i++;
	}
	return (ft_strdup(line));
}

char	*add_spaces(char *line, int count)
{
	t_space	space;

	space.i = 0;
	space.j = 0;
	space.len = ft_strlen(line);
	space.str = ft_calloc((space.len + (count * 2) + 1), 1);
	if (!space.str)
		return (NULL);
	else
		return (loop_spaces(space, line));
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
