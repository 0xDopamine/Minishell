/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:08:57 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 18:30:10 by abaioumy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_isdir(char *cmd)
{
	struct stat	path_stat;

	stat(cmd, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

void	ft_check_cmd(t_cmd *cmd, t_env **env_list)
{
	int	fds[2] = {0, 1};
	int in = 0;

	dispatch_pipe_node(cmd, &in, fds, env_list);
	if (fds[1] != 1)
		close(fds[1]), printf("%s:%d ---> %d\n", __FILE__, __LINE__, fds[1]);
	if (in != 0)
		close(in);

}

char	*exec_ifaccess(char *cmd)
{
	char	**path;
	char	*join;
	int		i;

	i = 0;
	path = ft_find_path();
	while (path[i])
	{
		join = ft_strjoin(path[i], cmd);
		if (access(join, X_OK) == 0)
		{
			ft_free_doubleptr(path);
			g_var.exit_status = EXIT_SUCCESS;
			return (join);
		}
		free(join);
		i++;
	}
	ft_free_doubleptr(path);
	return (NULL);
}
