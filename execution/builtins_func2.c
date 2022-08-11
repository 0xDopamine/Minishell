/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_func2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:17:11 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/11 17:46:13 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_cd(t_exec *line, t_env **env_list)
{
	t_env	*env;
	char	*pwd;
	char	*old_pwd;
	t_env	*head;

	head = *env_list;
	pwd = getcwd(NULL, 0);
	old_pwd = getcwd(NULL, 0);
	env = *env_list;
	if (!getcwd(old_pwd, PATH_MAX))
	{
		perror("cd");
		return (1);
	}
	while (env)
	{
		if (!ft_strncmp(env->content, "OLDPWD", 6))
		{
			free(env->content);
			env->content = ft_strjoin("OLDPWD=", old_pwd);
			break ;
		}
		env = env->next;
	}
	if (chdir(line->argv[1]) < 0)
	{
		perror("cd");
		g.exit_status = 2;
		return (1);
	}
	if (!getcwd(pwd, PATH_MAX))
	{
		perror("cd");
		return (1);
	}
	while (head)
	{
		if (!ft_strncmp(head->content, "PWD=", 4))
		{
			free(head->content);
			head->content = ft_strjoin("PWD=", pwd);
			break ;
		}
		head = head->next;
	}
	g.exit_status = 0;
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
		perror("pwd");
		g.exit_status = EXIT_FAILURE;
		return (1);
	}
	printf("%s\n", getcwd(s, 100));
	free(s);
	g.exit_status = EXIT_SUCCESS;
	return (1);
}

int	ft_env(t_env *env_list)
{
	while (env_list)
	{
		printf("%s", env_list->type);
		printf("%s\n", env_list->content);
		env_list = env_list->next;
	}
	g.exit_status = EXIT_SUCCESS;
	return (1);
}

// static	int	ft_ifexists_export(char *str, t_env *env)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (!ft_strncmp(str[i], env->content, ft_strlen(str)))
// 			return (0);
// 		i++;
// 		env = env->next;
// 	}
// 	return (1);
// }

// static int ft_check_export(char *str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (!(str[i] >= 65 && str[i] <= 90) && !(str[i] >= 97 && str[i] <= 122) && str[i] != '=' && str[i] != '+' && str[i] != '-')
// 			return (0);
// 		if ((str[i] == '+' || str[i] == '-') && str[i+1] == '=')
// 		{
// 			printf("export: not valid in this context");
// 			return (0);
// 		}
// 		i++;
// 	}
// 	return (1);
// }

int	ft_export(t_env **env, t_exec *line)
{
	if (!line->argv[1])
		return (ft_env(*env));
	// if (ft_ifexists_export(line->argv[1], *env))
	// 	ft_unset(env, line);
	// if (ft_check_export(line->argv[1]))
	// 	ft_lstadd_back(env, ft_lstnew(line->argv[1]));
	// else
	// 	printf("error\n");
	return (1);
}