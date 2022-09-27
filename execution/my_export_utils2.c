/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 20:17:08 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 18:30:10 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static	void	free_str(char **str)
{
	free(str[0]);
	free(str[1]);
	free(str);
}

int	export_checknbr(char ch)
{
	if (ch >= '0' && ch <= '9')
	{
		g_var.exit_status = EXIT_FAILURE;
		ft_putstr_fd("export: not valid in this context\n",
			NULL, STDERR_FILENO);
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}

int	export1(char *str1, char *str2, char **str, t_env **env)
{
	if (export_ifexists(str1, str2, env))
	{
		g_var.exit_status = EXIT_SUCCESS;
		return (1);
	}
	export_checkav(str2, str, PATH);
	return (0);
}

void	export_addvar(char **av, t_env **env)
{
	int		i;
	char	**str;

	i = 1;
	while (av[i])
	{
		str = ft_split_namecont(av[i]);
		if (!str)
			return ;
		if (!str[0])
			return (free_str(str));
		if (export1(str[0], str[1], str, env))
			return (free_str(str));
		if (export_checkav(str[0], str, NAME))
		{
			g_var.exit_status = EXIT_SUCCESS;
			ft_lstadd_back(env, ft_lstnew(str[1], str[0]));
			free(str);
		}
		else
			free_str(str);
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
