/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 20:17:08 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/11 20:22:30 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	**export_swap(t_env *head, char **names)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	temp = NULL;
	while (i < ft_lstsize(head))
	{
		j = i + 1;
		while (j < ft_lstsize(head) && names[j])
		{
			if (ft_strcmp(names[i], names[j]) > 0)
			{
				temp = names[i];
				names[i] = names[j];
				names[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (names);
}
