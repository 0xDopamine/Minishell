/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:55:10 by mbaioumy          #+#    #+#             */
/*   Updated: 2021/11/08 16:06:16 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
/*int	main(int argc, char **argv)
{
	char str[50] = "Nibbas in paris";
	ft_bzero(str, 10);
	printf("%s", str);
	return 0;
}*/
