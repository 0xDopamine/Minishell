/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 20:17:08 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/12 15:29:50 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	export_addvar(char **av, t_env **env)
{
	int		i;
	char	**str;

	i = 1;
	while (av[i])
	{
		str = ft_split_namecont(av[i]);
		if (!str || !str[0])
			return ;
		if (export_ifexists(str[0], str[1], env))
		{
			g.exit_status = EXIT_SUCCESS;
			return ;
		}
		if (export_checkav(str[0], str, NAME) && export_checkav(str[1], str, PATH))
		{
			g.exit_status = EXIT_SUCCESS;
			ft_lstadd_back(env, ft_lstnew(str[1], str[0]));
		}
		i++;
	}
}

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
