/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 02:28:40 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/26 02:30:19 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exec.h"

char    *set_free(char *ptr, char **dptr, char *return_value)
{
	if (ptr)
		free(ptr);
	freethis(dptr);
	return (return_value);
}