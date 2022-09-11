/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:54:34 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/10 23:12:32 by mbaioumy         ###   ########.fr       */
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