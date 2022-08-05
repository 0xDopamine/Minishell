/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_func2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:17:11 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/05 13:53:49 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_cd(char *dir)
{
	
	if (chdir(dir) < 0)
	{
		perror("chdir");
		return (1);
	}
	return (1);
}

int	ft_pwd(void)
{
	char *s;

	s = NULL;
	// s = ft_strdup("");
	if (getcwd(s, 100) == NULL)
	{
		free(s);
		perror("getcwd");
		exit (1);
	}
	printf("%s\n", getcwd(s, 100));
	free(s);
	return (1);
}

int	ft_env(t_env *env_list)
{
	while (env_list)
	{
		printf("%s\n", env_list->content);
		env_list = env_list->next;
	}
	return (1);
}

int	ft_export(t_env **env, t_exec *line)
{
	if (!line->argv[1])
		return (ft_env(*env));
	ft_lstadd_back(env, ft_lstnew(line->argv[1]));
	return (1);
}