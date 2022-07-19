/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:54:34 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/07/19 21:01:06 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && i < n - 1)
	{
		if (s1[i] == s2[i])
			i++;
		else
			break ;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_isalpha(int c)
{
	if (c >= 65 && c <= 90)
		return (1);
	if (c >= 97 && c <= 122)
		return (1);
	else
		return (0);
}

void    *ft_calloc (size_t count, size_t size)
{
    unsigned int    len;
    void    *ptr;

    len = count * size;
    ptr = malloc(len * sizeof(char));
    if (!ptr)
        return NULL;
    ft_bzero(ptr, len);
    return ptr;
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*tab;
	size_t	total;
	int		i;
	int		pos;

	pos = 0;
	i = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	total = ft_strlen(s1) + ft_strlen(s2) + 1;
	tab = (char *)ft_calloc(total + 1, sizeof(char));
	if (!tab)
		return (NULL);
	while (s1[i])
		tab[pos++] = s1[i++];
	i = 0;
	while (s2[i])
		tab[pos++] = s2[i++];
	return (tab);
}