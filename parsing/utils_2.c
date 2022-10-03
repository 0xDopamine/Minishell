/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:54:34 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/23 17:41:05 by abaioumy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	ft_isalpha(int c)
{
	if (c >= 65 && c <= 90)
		return (1);
	if (c >= 97 && c <= 122)
		return (1);
	if (ft_strchr((char)c, " \t\f\n\v\r"))
		return (1);
	else
		return (0);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned int	len;
	void			*ptr;

	len = count * size;
	ptr = malloc(len * sizeof(char));
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, len);
	return (ptr);
}

int	ft_isalnum(int arg)
{
	if ((arg >= 48 && arg <= 57) || (arg >= 97 && arg <= 122)
		|| (arg >= 65 && arg <= 90) || arg == 36)
		return (1);
	else
		return (0);
}

int	num_words(char *str, int quote_flag)
{
	int		words;
	char	**split;
	int		i;

	words = 1;
	i = -1;
	if (quote_flag)
		split = ft_split(str, ' ');
	else
		split = ft_split_q(str, ' ');
	if (split == NULL)
		return (0);
	while (split[++i])
		words++;
	freethis(split);
	return (words);
}

int	is_whitespace(char *str)
{
	char	*whitespaces;
	int		i;
	int		j;

	whitespaces = ft_strdup("\n\t\r\v ");
	i = 0;
	while (str[i])
	{
		j = 0;
		while (whitespaces[j])
		{
			if (whitespaces[j] == str[i])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
