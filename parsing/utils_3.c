/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:55:10 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/08/25 09:55:50 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len] != '\0')
		len++;
	return (len);
}

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

char	*ft_strdup(char *src)
{
	int		i;
	size_t	len;
	char	*dest;

	i = 0;
	if (!src)
		return (NULL);
	len = ft_strlen(src);
	dest = (char *)malloc(sizeof(char) * len + 1);
	if (!dest)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	ft_bzero(void *s, size_t n)
{
	int	i;
	char *str = (char *)s;

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
	return(str);
}

int		check(char before, char after)
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
	while (line[i])
	{
		if (line[i] == '|')
			if (line[i - 1] != ' ' || line[i + 1] != ' ')
				return(handle_spaces(line));
		i++;
	}
	return (line);
}
