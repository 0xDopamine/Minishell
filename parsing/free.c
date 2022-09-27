/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 02:28:40 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/27 04:07:33 by mbaioumy         ###   ########.fr       */
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
