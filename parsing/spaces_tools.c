/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 02:14:07 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/28 20:17:46 by codespace        ###   ########.fr       */
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
	count = 0;
	while (line[i])
	{
		if (ft_strchr(line[i], "|<>"))
		{
			if (i > 0 && (line[i] == '>' && line[i + 1] == '>'))
			{
				if (!check(line[i - 1], line[i + 2]) && line)
					count += 2;
			}
			else if (i > 0 && (line[i - 1] != ' ' || line[i + 1] != ' '))
					count += 1;
		}
		i++;
	}
	if (count > 0)
	{
		temp = (line);
		line = add_spaces(temp, count);
		// free(temp);
		return (line);
	}
	return (line);
}

char	*spaces(char *line)
{
	int		i;
	// char	*temp;

	i = 0;
	if (!line)
	{
		free(line);
		return (NULL);
	}
	if (ft_strlen(line) == 1)
		return (ft_strdup(line));
	while (line[i])
	{
		if (ft_strchr(line[i], "|<>") && !ft_is_heredoc(line))
		{
			if (i > 0 && (line[i - 1] != ' ' || line[i + 1] != ' '))
			{
				line = handle_spaces(line);
				return (line);
			}
		}
		i++;
	}
	return (ft_strdup(line));
}

char	*add_spaces(char *line, int count)
{
	t_space	space;
	// char	*temp;

	space.i = 0;
	space.j = 0;
	space.len = ft_strlen(line);
	space.str = malloc(sizeof(char) * (space.len + (count * 2) + 1));
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
