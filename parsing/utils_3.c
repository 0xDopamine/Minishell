/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:55:10 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/01 02:15:36 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*findthewae(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strncmp(str[i], "PATH=", 5) == 0)
			return (str[i] + 5);
		i++;
	}
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	int		i;
	char	*str;

	str = (char *)s;
	i = 0;
	while (i < (int)n)
	{
		str[i] = '\0';
		i++;
	}
}

char	*add_spaces(char *line, int count)
{
	int		i;
	int		j;
	char	*str;
	int		len;

	i = 0;
	j = 0;
	len = ft_strlen(line);
	str = malloc(sizeof(char) * (len + (count * 2) + 1));
	while (line[i])
	{
		if (ft_strchr(line[i], "|<>"))
		{
			str[j] = ' ';
			if (line[i] == '>' && line[i + 1] == '>')
			{
				str[j + 1] = line[i];
				str[j + 2] = line [i + 1];
				str[j + 3] = ' ';
				j += 4;
				i += 2;
			}
			else
			{
				str[j + 1] = line[i];
				str[j + 2] = ' ';
				j += 3;
				i++;
			}
		}
		else
		{
			str[j] = line[i];
			i++;
			j++;
		}
	}
	str[j] = '\0';
	free(line);
	return (str);
}
