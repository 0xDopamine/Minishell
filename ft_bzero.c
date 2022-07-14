/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:55:10 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/07/14 20:11:55 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
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
/*int	main(int argc, char **argv)
{
	char str[50] = "Nibbas in paris";
	ft_bzero(str, 10);
	printf("%s", str);
	return 0;
}*/
