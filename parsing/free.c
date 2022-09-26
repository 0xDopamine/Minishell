/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 02:28:40 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/26 13:20:19 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exec.h"

char	*set_free(char *ptr, char **dptr, char *return_value)
{
	if (ptr)
		free(ptr);
	freethis(dptr);
	return (return_value);
}
