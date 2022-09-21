/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 12:31:59 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 18:30:10 by abaioumy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	unset_checkstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= 65 && str[i] <= 90)
			&& !(str[i] >= 97 && str[i] <= 122)
			&& str[i] != '_')
		{
			ft_putstr_fd("unset: '", str, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", NULL, STDERR_FILENO);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_FAILURE);
}

int	ft_unset(t_env **env, t_exec *line)
{
	t_env	*env2;
	t_env	*prev;

	env2 = *env;
	prev = env2;
	if (line->argv[1] == NULL)
	{
		g_var.exit_status = EXIT_SUCCESS;
		return (1);
	}
	unset_loop(env2, prev, line->argv);
	return (1);
}
