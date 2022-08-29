/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 12:31:59 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/29 02:18:49 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// static	void	unset_checkstr(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (!(str[i] >= 65 && str[i] <= 90)
// 				&& !(str[i] >= 97 && argv[i] <= 122)
// 				&& argv[j][i] != '_' && !(argv[j][i] >= '0'
// 				&& argv[j][i] <= '9'))
// 			{
// 				ft_putstr_fd("unset: '", argv[j], STDERR_FILENO);
// 				ft_putstr_fd("': not a valid identifier\n", NULL, STDERR_FILENO);
// 				return (1);
// 			}
// 			i++;
// 		}
// }

static	int	unset_checkname(char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (argv[1][0] >= '0' && argv[1][0] <= '9')
	{
		ft_putstr_fd("unset: '", argv[1], STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", NULL, STDERR_FILENO);
		return (1);
	}
	while (argv[j])
	{
		i = 0;
		// unset_checkstr(argv[j]);
		while (argv[j][i])
		{
			if (!(argv[j][i] >= 65 && argv[j][i] <= 90)
				&& !(argv[j][i] >= 97 && argv[j][i] <= 122)
				&& argv[j][i] != '_' && !(argv[j][i] >= '0'
				&& argv[j][i] <= '9'))
			{
				ft_putstr_fd("unset: '", argv[j], STDERR_FILENO);
				ft_putstr_fd("': not a valid identifier\n", NULL, STDERR_FILENO);
				return (1);
			}
			i++;
		}
		j++;
	}
	return (0);
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
		return (1);
	}
	while (env2)
	{
		if (ft_envcmp(env2->name, line->argv[1]))
		{
			temp = env2;
			prev->next = temp->next;
			ft_lstdelone(env2, del);
			break ;
		}
		prev = env2;
		env2 = env2->next;
	}
	g.exit_status = EXIT_SUCCESS;
	return (1);
}
