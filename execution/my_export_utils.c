/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 15:51:47 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/06 17:05:43 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"


// int	ft_strcmp(char *s1, char *s2)
// {
// 	unsigned int	i;

// 	i = 0;
// 	while (s1[i] && s2[i] && s1[i] == s2[i])
// 		i++;
// 	return (s1[i] - s2[i]);
// }

// char	**export_sortnames(t_env *env_list)
// {
// 	char	**names;
// 	t_env	*tmp;
// 	t_env	*head;
// 	int		i;

// 	i = 0;
// 	head = env_list;
// 	tmp = env_list;
// 	names = (char **)malloc(sizeof(char *) * ft_lstsize(env_list) + 1);
// 	while (names[i])
// 	{
// 		names[i++] = ft_strdup(env_list->name);
// 		env_list = env_list->next;
// 	}
// 	names[i] = NULL;
// 	while (names[i])
// 	{
		
// 	}
// 	return (names);
// }

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
		if ((!(str[i] >= 65 && str[i] <= 90)
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
