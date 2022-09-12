/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 20:25:04 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/12 12:09:21 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	**unset_copyargs(char **av, char **args)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (av[i])
	{
		args[j] = ft_strdup(av[i]);
		j++;
		i++;
	}
	printf("%d\n", j);
	args[j] = NULL;
	return (args);
}

void	unset_loop(t_env *env, t_env *temp, t_env *prev, char **args)
{
	int		i;
	t_env	*list;

	i = 1;
	list = env;
	prev = env;
	while (args[i])
	{
		list = env;
		while (list)
		{
			if (ft_envcmp(list->name, args[i]))
			{
				temp = list;
				prev->next = temp->next;
				ft_lstdelone(list, del);
				break ;
			}
			prev = list;
			list = list->next;
		}
		i++;
	}
}
