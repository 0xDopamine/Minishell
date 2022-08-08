/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:58:53 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/08 14:09:21 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "header.h"

void    ft_redirect(t_redir *redir, char **env, t_env **env_list)
{
    int fd_file;
    t_exec  *ex;

    ex = (t_exec *)redir->cmd;
    printf("%s %s\n", ex->argv[0], redir->file);
    fd_file = open(redir->file, redir->mode, 0644);
    dup2(fd_file, redir->fd);
    //close(fd_file);
    ft_exec(ex, env, env_list);
}