/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 02:28:40 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/28 04:50:45 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exec.h"

char	*set_free(char *ptr, char *ptr2, char **dptr, char *returnval)
{
	if (ptr)
		free(ptr);
	if (ptr2)
		free(ptr2);
	if (dptr)
		freethis(dptr);
	return (returnval);
}

char	*strjoin_and_free1(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	return (res);
}

char	*strjoin_and_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (s2)
		free(s2);
	if (s1)
		free(s1);
	return (res);
}
