/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 13:49:02 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/14 22:18:12 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_ifmybuiltin_up(char *cmd, t_exec *line, t_env **env_list)
{
	if (!cmd)
		return (0);
	if (strncmp(cmd, "ECHO", ft_strlen(cmd)) == 0)
		return (ft_echo(line, STDOUT_FILENO));
	else if (strncmp(cmd, "PWD", ft_strlen(cmd)) == 0)
		return (ft_pwd());
	else if (!ft_strncmp(cmd, "ENV", ft_strlen(cmd)))
		return (ft_env(*env_list, ENV));
	else
		return (0);
}

int	ft_ifmybuiltin(char *cmd, t_exec *line, t_env **env_list)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
		return (ft_echo(line, STDOUT_FILENO));
	else if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
		return (ft_cd(line, env_list));
	else if (strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
		return (ft_pwd());
	else if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
		return (ft_export(env_list, line));
	else if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
		return (ft_unset(env_list, line));
	else if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
		return (ft_env(*env_list, 'a'));
	else if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
		return (ft_exit(line->argv));
	else
		return (0);
}
