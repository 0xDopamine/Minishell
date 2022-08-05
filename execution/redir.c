/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:58:53 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/04 12:10:25 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "header.h"

void    ft_redirect(t_redir *redir)
{
    int fd_file;
    
    fd_file = open(redir->file, redir->mode, 0644);
    dup2(fd_file, redir->fd);
    // pid = fork();
    // if (pid < 0)
    // {
    //     perror("fork");
    //     exit(1);
    // }
    // if (pid == 0)
}