/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:54:34 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/07/14 20:19:35 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

/*int main(void)
{
    char *ptr;
    ptr = calloc(4, 20);
    printf("%i", ptr[2]);
}*/
 /*int    main()
 {
     char *str;
     char *str1;

    str = (char *)ft_calloc(6, sizeof(int));
    str1 = (char *)calloc(6, sizeof(char));
     //str = "Hellooo";
     printf("%s\n%s", str, str1);

     return 0;
 }*/