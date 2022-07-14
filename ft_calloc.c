/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:54:34 by mbaioumy          #+#    #+#             */
/*   Updated: 2021/11/12 13:35:40 by mbaioumy         ###   ########.fr       */
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