/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 19:24:08 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/18 22:00:09 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_cmd	*parsecmd(char *s)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	next(&s, "");
	if (s)
	{
		exit(2);
	}
	return (cmd);
}

t_cmd	*execcmd(int words)
{
	t_exec	*ex;

	ex = malloc(sizeof(t_exec));
	ex->argv = malloc(sizeof(char *) * words + 1);
	ex->type = EXEC;
	return ((t_cmd *)ex);
}

t_redir	*redircmd_test(t_cmd *cmd, char *q, int mode, int fd)
{
	t_redir	*red;

	red = malloc(sizeof(t_redir));
	red->cmd = cmd;
	red->file = q;
	red->mode = mode;
	red->type = REDIR;
	red->fd = fd;
	red->next = NULL;
	return (red);
}

t_cmd	*pipecmd(t_cmd *left, t_cmd *right)
{
	t_pipe	*pipe;

	pipe = malloc(sizeof(t_pipe));
	pipe->left = left;
	pipe->right = right;
	pipe->type = PIPE;
	return ((t_cmd *)pipe);
}
