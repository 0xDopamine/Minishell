/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 20:11:35 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/13 18:28:54 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	env_printloop(t_env *list, char **names, int i)
{
	while (list)
	{
		if (ft_strcmp(list->name, names[i]) == 0)
		{
			if (list->ifnull == 1)
				printf("\n");
			if (list->path != NULL && list->ifnull != 1)
			{
				printf("=");
				printf("%c%s%c\n", '"', list->path, '"');
			}
		}
		list = list->next;
	}
}
