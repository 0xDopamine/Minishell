/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 13:49:02 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/01 13:07:31 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_ifmybuiltin_up(char *cmd, char **mybuiltins,
	t_exec *line, t_env **env_list)
{
	if (!strncmp(cmd, mybuiltins[0], ft_strlen(mybuiltins[0])))
		return (ft_echo(line));
	else if (!strncmp(cmd, mybuiltins[1], ft_strlen(mybuiltins[1])))
		return (ft_pwd());
	else if (!ft_strncmp(cmd, mybuiltins[2], ft_strlen(mybuiltins[2])))
		return (ft_env(*env_list, 'a'));
	else
		return (0);
}

int	ft_builtins_up(char *cmd, t_exec *line, t_env **env_list)
{
	char	**mybuiltins;
	int		i;
	int		ret;

	i = 0;
	mybuiltins = (char **)malloc(3 * sizeof(char *));
	if (!mybuiltins)
		return (0);
	mybuiltins[0] = ft_strdup("ECHO");
	mybuiltins[1] = ft_strdup("PWD");
	mybuiltins[2] = ft_strdup("ENV");
	ret = ft_ifmybuiltin_up(cmd, mybuiltins, line, env_list);
	while (i < 3)
		free(mybuiltins[i++]);
	free(mybuiltins);
	return (ret);
}

int	ft_ifmybuiltin(char *cmd, char **mybuiltins,
	t_exec *line, t_env **env_list)
{
	if (!strncmp(cmd, mybuiltins[0], ft_strlen(mybuiltins[0])))
		return (ft_echo(line));
	else if (!ft_strncmp(cmd, mybuiltins[1], ft_strlen(mybuiltins[1])))
		return (ft_cd(line, env_list));
	else if (!strncmp(cmd, mybuiltins[2], ft_strlen(mybuiltins[2])))
		return (ft_pwd());
	else if (!ft_strncmp(cmd, mybuiltins[3], ft_strlen(mybuiltins[3])))
		return (ft_export(env_list, line));
	else if (!ft_strncmp(cmd, mybuiltins[4], ft_strlen(mybuiltins[4])))
		return (ft_unset(env_list, line));
	else if (!ft_strncmp(cmd, mybuiltins[5], ft_strlen(mybuiltins[5])))
		return (ft_env(*env_list, 'a'));
	else if (!ft_strncmp(cmd, mybuiltins[6], ft_strlen(mybuiltins[6])))
		return (ft_exit(line->argv));
	else
		return (0);
}

int	ft_builtins(char *cmd, t_exec *line, t_env **env_list)
{
	char	**mybuiltins;
	int		i;
	int		ret;

	i = 0;
	mybuiltins = (char **)malloc(7 * sizeof(char *));
	if (!mybuiltins)
		return (0);
	mybuiltins[0] = ft_strdup("echo");
	mybuiltins[1] = ft_strdup("cd");
	mybuiltins[2] = ft_strdup("pwd");
	mybuiltins[3] = ft_strdup("export");
	mybuiltins[4] = ft_strdup("unset");
	mybuiltins[5] = ft_strdup("env");
	mybuiltins[6] = ft_strdup("exit");
	ret = ft_ifmybuiltin(cmd, mybuiltins, line, env_list);
	if (ret == 0)
		ret = ft_builtins_up(cmd, line, env_list);
	while (i < 7)
		free(mybuiltins[i++]);
	free(mybuiltins);
	return (ret);
}
