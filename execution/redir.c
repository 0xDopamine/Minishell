/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:58:53 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/05 15:01:21 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "header.h"

void    ft_redirect(t_redir *redir, t_exec *line, char **env, t_env **env_list)
{
    int fd_file;

    fd_file = open(redir->file, redir->mode, 0644);
    dup2(fd_file, redir->fd);
    ft_exec(line, env, env_list);
}