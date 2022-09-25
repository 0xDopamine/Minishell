/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 13:49:02 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/25 15:08:36 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_ifmybuiltin_up(char *cmd, t_exec *line, t_env **env_list)
{
	if (!cmd)
		return (0);
	if (strcmp(cmd, "ECHO") == 0)
		return (ft_echo(line, STDOUT_FILENO));
	else if (strcmp(cmd, "PWD") == 0)
		return (ft_pwd());
	else if (!ft_strcmp(cmd, "ENV"))
		return (ft_env(*env_list, ENV));
	else
		return (0);
}

int	ft_ifmybuiltin(char *cmd, t_exec *line, t_env **env_list)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (ft_echo(line, STDOUT_FILENO));
	else if (ft_strcmp(cmd, "cd") == 0)
		return (ft_cd(line, env_list));
	else if (strcmp(cmd, "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(cmd, "export") == 0)
		return (ft_export(env_list, line));
	else if (ft_strcmp(cmd, "unset") == 0)
		return (ft_unset(env_list, line));
	else if (ft_strcmp(cmd, "env") == 0)
		return (ft_env(*env_list, 'a') );
	else if (ft_strcmp(cmd, "exit") == 0)
		return (ft_exit(line->argv));
	else
		return (0);
}
