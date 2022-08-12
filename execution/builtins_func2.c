/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_func2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:17:11 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/12 14:29:09 by abaioumy         ###   ########.fr       */
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
		if (!ft_strncmp(env->type, "OLDPWD", 6))
		{
			free(env->content);
			env->content = old_pwd;
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
		if (!ft_strncmp(head->type, "PWD", 3))
		{
			free(head->content);
			head->content = pwd;
			break ;
		}
		head = head->next;
	}
	g.exit_status = 0;
	return (1);
}

int	ft_pwd(t_exec *line)
{
	char	*s;

	s = NULL;
	if (line->argv[1])
	{
		ft_putstr_fd("pwd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (getcwd(s, PATH_MAX) == NULL)
	{
		free(s);
		perror("pwd");
		g.exit_status = EXIT_FAILURE;
		return (1);
	}
	printf("%s\n", getcwd(s, PATH_MAX));
	free(s);
	g.exit_status = EXIT_SUCCESS;
	return (1);
}

int	ft_env(t_env *env_list)
{
	while (env_list)
	{
		printf("%s", env_list->type);
		printf("=");
		printf("%s\n", env_list->content);
		env_list = env_list->next;
	}
	g.exit_status = EXIT_SUCCESS;
	return (1);
}

static	int	ft_ifexists_export(char *type, char *content, t_env **env)
{
	int		i;
	t_env	*lst;

	i = 0;
	lst = *env;
	while (lst)
	{
		if (!ft_strncmp(type, lst->type, ft_strlen(lst->type)))
		{
			free(lst->content);
			lst->content = content;
			return (1);
		}
		i++;
		lst = lst->next;
	}
	return (0);
}

static int ft_check_export(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= 65 && str[i] <= 90) && !(str[i] >= 97 && str[i] <= 122) && str[i] != '=' && str[i] != '+' && str[i] != '-')
			return (0);
		if ((str[i] == '+' || str[i] == '-') && str[i+1] == '=')
		{
			printf("export: not valid in this context\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_export(t_env **env, t_exec *line)
{
	char	**str;

	str = NULL;
	if (!line->argv[1])
		return (ft_env(*env));
	str = ft_split_typecont(line->argv[1]);
	if (ft_ifexists_export(str[0], str[1], env))
		return (1);
	if (ft_check_export(line->argv[1]))
	{
		ft_lstadd_back(env, ft_lstnew(str[1], str[0]));
	}
	else
		printf("error\n");
	return (1);
}