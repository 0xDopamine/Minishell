/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 19:51:27 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 05:39:44 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <unistd.h>

t_cmd	*parseexec(char **ps, t_env *env_list)
{
	t_exec	*cmd;
	t_cmd	*ret;
	t_parse	*parse;

	parse = malloc(sizeof(t_parse));
	parse->words = ft_init_words(ps);
	ret = execcmd(parse->words);
	cmd = (t_exec *)ret;
	parse->argc = 0;
	ret = parseredir(ret, ps);
	while (!next(ps, "|"))
	{
		parse->tok = get_token(ps, &parse->q);
		if (parse->tok == 0)
			break ;
		ft_append_command(cmd, parse, env_list);
		printf("cmd: %s\n", cmd->argv[parse->argc]);
		parse->argc++;
		if (parse->argc >= parse->words || parse->split[1] == NULL)
			break ;
		ret = parseredir(ret, ps);
		if (ret == NULL)
			return (NULL);
	}
	cmd->argv[parse->argc] = NULL;
	free(parse);
	return (ret);
}

t_cmd	*parseredir(t_cmd *cmd, char **ps)
{
	t_parse	*parse;
	t_redir	*head;

	parse = malloc(sizeof(t_parse));
	parse->split = NULL;
	if (cmd->type == EXEC)
		head = NULL;
	if (cmd->type == REDIR)
		head = (t_redir *)cmd;
	while (next(ps, "<>"))
	{
		parse->tok = get_token(ps, 0);
		if (get_token(ps, &parse->q) != 'c')
		{
			ft_putstr_fd("syntax error\n", NULL, STDERR_FILENO);
			cmd = NULL;
			return (cmd);
		}
		if (*parse->q)
			parse->split = ft_split(parse->q, ' ');
		ft_append_redir_list(&head, parse, cmd);
		cmd = (t_cmd *)head;
	}
	free(parse);
	return (cmd);
}

t_cmd	*parsepipe(char **ps, t_env *env_list)
{
	t_cmd	*cmd;

	cmd = parseexec(ps, env_list);
	if (cmd == NULL)
		return (NULL);
	if (next(ps, "|"))
	{
		get_token(ps, 0);
		cmd = pipecmd(cmd, parsepipe(ps, env_list));
	}
	return (cmd);
}
