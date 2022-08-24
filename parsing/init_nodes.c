/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 19:24:08 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/08/24 04:28:04 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

//returns ptr to the tree it built
t_cmd	*parsecmd(char *s)
{
	t_cmd	*cmd;
	
	cmd = malloc(sizeof(t_cmd));
	// advance past any whitespace
	next(&s, "");
	if (s)
	{
		printf("leftovers: %s\n", s);
		exit(2);
	}
	// walk a tree, replace all chars after names with NULL to be null terminated strings
	//nulterminate(cmd);
	return (cmd);
}

t_cmd   *execcmd(int words)
{
    t_exec  *ex;

    ex = malloc(sizeof(t_exec));
    ex->argv = malloc(sizeof(char *) * words + 1);
	ex->type = EXEC;
	// ex->argv = ps;
    return ((t_cmd *)ex);
}

t_cmd   *redircmd(t_cmd *cmd, char *q, int mode, int fd)
{
    t_redir *red;

    red = malloc(sizeof(t_redir));
    red->cmd = cmd;
    red->file = q;
    red->mode = mode;
    red->type = REDIR;
    red->fd = fd;

    return ((t_cmd *)red);
}

t_cmd	*pipecmd(t_cmd *left, t_cmd *right)
{
	t_pipe	*pipe;

	pipe = malloc(sizeof(t_pipe));
	pipe->left = left;
	pipe->right = right;
	pipe->type = PIPE;
	return ((t_cmd*)pipe);
}

