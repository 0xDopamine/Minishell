/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 12:31:59 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/11 20:26:11 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static	int	unset_checkstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= 65 && str[i] <= 90)
			&& !(str[i] >= 97 && str[i] <= 122)
			&& str[i] != '_' && !(str[i] >= '0'
				&& str[i] <= '9'))
		{
			ft_putstr_fd("unset: '", str, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", NULL, STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static	int	unset_checkname(char **argv)
{
	int	j;

	j = 0;
	if (argv[1][0] >= '0' && argv[1][0] <= '9')
	{
		ft_putstr_fd("unset: '", argv[1], STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", NULL, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	while (argv[j])
	{
		if (unset_checkstr(argv[j]))
			return (EXIT_FAILURE);
		j++;
	}
	return (EXIT_SUCCESS);
}

int	ft_unset(t_env **env, t_exec *line)
{
	t_env	*env2;
	t_env	*temp;
	t_env	*prev;

	temp = *env;
	env2 = *env;
	prev = env2;
	if (unset_checkname(line->argv))
	{
		g.exit_status = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	unset_loop(env2, temp, prev, line->argv[1]);
	g.exit_status = EXIT_SUCCESS;
	return (1);
}
