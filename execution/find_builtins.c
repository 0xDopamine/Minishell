/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 13:49:02 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/11 16:11:34 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_ifmybuiltin(char *cmd, char **mybuiltins, t_exec *line, t_env **env_list)
{
	if (!strncmp(cmd, mybuiltins[0], ft_strlen(cmd)))
		return (ft_echo(line, *env_list));
	else if (!ft_strncmp(cmd, mybuiltins[1], ft_strlen(cmd)))
		return (ft_cd(line, env_list));
	else if (!strncmp(cmd, mybuiltins[2], ft_strlen(cmd)))
		return (ft_pwd());
	else if (!ft_strncmp(cmd, mybuiltins[3], ft_strlen(cmd)))
		return (ft_export(env_list, line));
	else if (!ft_strncmp(cmd, mybuiltins[4], ft_strlen(cmd)))
		return (ft_unset(env_list, line));
	else if (!ft_strncmp(cmd, mybuiltins[5], ft_strlen(cmd)))
		return (ft_env(*env_list));
	else if (!ft_strncmp(cmd, mybuiltins[6], ft_strlen(cmd)))
		return (ft_exit());
	else
		return (0);
}

int	ft_builtins(char *cmd, t_exec *line, t_env **env_list)
{
	char **mybuiltins;
	int	i;

	i = 0;
	mybuiltins = (char **)malloc(8 * sizeof(char *));
	mybuiltins[0] = ft_strdup("echo");
	mybuiltins[1] = ft_strdup("cd");
	mybuiltins[2] = ft_strdup("pwd");
	mybuiltins[3] = ft_strdup("export");
	mybuiltins[4] = ft_strdup("unset");
	mybuiltins[5] = ft_strdup("env");
	mybuiltins[6] = ft_strdup("exit");
	mybuiltins[7] = NULL;
	return (ft_ifmybuiltin(cmd, mybuiltins, line, env_list));
}
