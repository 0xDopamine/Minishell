/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 20:11:35 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/25 16:54:16 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	env_printloop(t_env *list, char **names, int i)
{
	while (list)
	{
		if (ft_strcmp(list->name, names[i]) == 0)
		{
			if (list->path != NULL)
			{
				printf("=");
				printf("%c%s%c\n", '"', list->path, '"');
			}
			if (list->path == NULL)
				printf("\n");
		}
		list = list->next;
	}
}
