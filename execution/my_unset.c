/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 12:31:59 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/12 14:59:00 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// static	int	unset_argslen(char **av)
// {
// 	int	i;
// 	int	len;

// 	i = 1;
// 	len = 0;
// 	while (av[i])
// 	{
// 		printf("%s\n", av[i]);
// 		i++;
// 		len++;
// 	}
// 	printf("%d\n", len);
// 	return (len);
// }

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
	t_env	*temp;
	t_env	*prev;

	temp = *env;
	env2 = *env;
	prev = env2;
	if (line->argv[1] == NULL)
	{
		g.exit_status = EXIT_SUCCESS;
		return (1);
	}
	// if (unset_checkname(line->argv))
	// {
	// 	g.exit_status = EXIT_FAILURE;
	// 	return (EXIT_FAILURE);
	// }
	unset_loop(env2, temp, prev, line->argv);
	return (1);
}
