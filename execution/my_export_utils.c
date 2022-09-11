/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 15:51:47 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/11 20:19:50 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	**export_sortnames(t_env *env_list)
{
	char	**names;
	int		i;
	t_env	*head;

	i = 0;
	head = env_list;
	names = (char **)ft_calloc(sizeof(char *), ft_lstsize(head));
	while (i < ft_lstsize(head) && env_list)
	{
		names[i++] = ft_strdup(env_list->name);
		env_list = env_list->next;
	}
	i = 0;
	return (export_swap(head, names));
}

int	export_ifnotreplace(char *str, t_env *env_list)
{
	while (env_list)
	{
		if (!ft_strncmp(str, env_list->name, ft_strlen(str)))
		{
			printf("hello\n");
			return (1);
		}
		env_list = env_list->next;
	}
	return (0);
}

int	export_checkname(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= 65 && str[i] <= 90)
			&& !(str[i] >= 97 && str[i] <= 122)
			&& !(str[i] >= '0' && str[i] <= '9') && str[i] != '_')
		{
			g.exit_status = EXIT_FAILURE;
			ft_putstr_fd("export: not valid in this context\n",
				NULL, STDERR_FILENO);
			return (0);
		}
		i++;
	}
	return (1);
}

int	export_checkpath(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((!(str[i] >= 48 && str[i] <= 57) && !(str[i] >= 65 && str[i] <= 90)
				&& !(str[i] >= 97 && str[i] <= 122))
			|| (str[i] == '<' || str[i] == '>' || str[i] == '('
				|| str[i] == ')'))
		{
			g.exit_status = EXIT_FAILURE;
			ft_putstr_fd("export: not valid in this context\n",
				NULL, STDERR_FILENO);
			return (0);
		}
		i++;
	}
	return (1);
}
