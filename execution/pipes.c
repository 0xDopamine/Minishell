/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        +#+  +:+       +#+          */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:32:15 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 18:30:10 by abaioumy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_pipes(t_pipe *pipes, t_env **env_list, int *in)
{
	int	fds[2];

	pipe(fds);
	ft_start_pipe(pipes->left, in, fds, env_list);
	close(fds[1]);
	ft_start_pipe(pipes->right, &fds[0], (int [2]){0, 1}, env_list);
	close(fds[0]);
}
